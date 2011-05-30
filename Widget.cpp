#include "Widget.h"

using namespace std;

map<QWidget*, SoTextEdit*> g_textedit_map;
map<QWidget*, QString> g_filename_map;

Widget::Widget(QWidget * iParent, Qt::WindowFlags iFlags)
: QWidget(iParent, iFlags)
{
	proc = new QProcess(this);
	keyBind = new SOEKeyBind();
	makeWidgets();
}

void Widget::makeWidgets()
{
	countTab = 0;

	//for save&load
	m_FileLabel = new QLabel(tr("File :"));
	m_FileName = new QLineEdit(this);
	m_FileName->setMaxLength(LINE_SIZE);
	connect(m_FileName, SIGNAL(returnPressed()), this, SLOT(lineLoad()));
	m_SaveButton = new QPushButton(tr("&Save"));
	m_LoadButton = new QPushButton(tr("&Load"));
	connect(m_SaveButton, SIGNAL(clicked()), this, SLOT(buttonSave()));
	connect(m_LoadButton, SIGNAL(clicked()), this, SLOT(buttonLoad()));
	//

	m_CmdLabel = new QLabel(tr("Cmd:"));
	m_CmdLine = new QLineEdit(this);



	m_SettingButton = new QPushButton(tr("&Setting"));
	connect(m_SettingButton, SIGNAL(clicked()), this, SLOT(settingClickedSlot()));

	m_Tab = new QTabWidget(this);
	m_Tab->setTabShape(QTabWidget::Triangular);
	m_Tab->setUsesScrollButtons(true);
	m_Tab->setMovable(true);
	m_Tab->setTabsClosable(true);
	m_Tab->setDocumentMode(true);

	m_AddTab = new QToolButton(m_Tab);
	m_AddTab->setCursor(Qt::ArrowCursor);
	m_AddTab->setAutoRaise(true);
	m_AddTab->setIcon(QIcon("image/plus_icon.png"));
	m_Tab->setCornerWidget(m_AddTab, Qt::TopLeftCorner);

	m_h_StatusLayout = new QHBoxLayout();
	m_h_StatusLayout->addWidget(m_FileLabel);
	m_h_StatusLayout->addWidget(m_FileName);
	m_h_StatusLayout->addWidget(m_SaveButton);
	m_h_StatusLayout->addWidget(m_LoadButton);
	m_h_StatusLayout->addWidget(m_SettingButton);
	m_s_CmdLayout = new QHBoxLayout();
	m_s_CmdLayout->addWidget(m_CmdLabel);
	m_s_CmdLayout->addWidget(m_CmdLine);
	m_c_TextLayout = new QHBoxLayout();
	m_c_TextLayout->addWidget(m_Tab);

	m_v_WholeLayout = new QVBoxLayout;
	m_v_WholeLayout->addLayout(m_h_StatusLayout);
	m_v_WholeLayout->addLayout(m_s_CmdLayout);
	m_v_WholeLayout->addLayout(m_c_TextLayout);

	setLayout(m_v_WholeLayout);

	newTab();

	connect(m_AddTab, SIGNAL(clicked()), this, SLOT(newTab()));
	connect(m_Tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	connect(m_Tab, SIGNAL(currentChanged(int)), this, SLOT(filenameChange(int)));
	connect(m_Tab, SIGNAL(currentChanged(int)), this, SLOT(textCursorPositionChangedSlot1(int)));
	connect(keyBind, SIGNAL(CtrlF_PressedSignal()), this, SLOT(setCtrlF()));
	connect(keyBind, SIGNAL(CtrlB_PressedSignal()), this, SLOT(setCtrlB()));
	connect(keyBind, SIGNAL(CtrlN_PressedSignal()), this, SLOT(setCtrlN()));
	connect(keyBind, SIGNAL(CtrlP_PressedSignal()), this, SLOT(setCtrlP()));
	connect(m_CmdLine, SIGNAL(returnPressed()), this, SLOT(cmdExecSlot()));
	connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(appendViewSlot()));
}

void Widget::newTab()
{
	countTab ++;
	QString title = tr("new text field") + QString::number(countTab);
	m_Text = new SoTextEdit();
	m_Text->setPlainText(tr(""));
	m_Text->setCursorWidth(6);
	m_Text->ensureCursorVisible();
	m_Text->setFont(QFont("Arial",12));
	keyBind->setSOE_TextKeyBind(m_Text);
	m_Tab->addTab(m_Text, title);

	QTextCursor t_cursor = m_Text->textCursor();
	t_cursor.movePosition(QTextCursor::End);
	m_Text->setTextCursor(t_cursor);

	g_textedit_map.insert(map<QWidget*, SoTextEdit*>::value_type(m_Tab->widget(m_Tab->count() - 1), m_Text));
	g_filename_map.insert(map<QWidget*, QString>::value_type(m_Tab->widget(m_Tab->count() - 1), title));
	m_FileName->setText(title);
	connect(m_Text, SIGNAL(cursorPositionChanged()), this, SLOT(textCursorPositionChangedSlot2()));
	m_Tab->setCurrentIndex(m_Tab->count() - 1);
}

void Widget::setCtrlF()
{
	g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
}
void Widget::setCtrlB()
{
	g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
}
void Widget::setCtrlP()
{
	g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
}
void Widget::setCtrlN()
{
	g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
}

void Widget::textChecker()
{
	//m_Tab->widget(m_Tab->currentIndex())->setStyleSheet("color: red;");
}

void Widget::closeTab(int index)
{
	if(countTab > (tabRemoveChecker + 1))
	{
	  g_textedit_map.erase(m_Tab->widget(index));
	  g_filename_map.erase(m_Tab->widget(index));
	  tabRemoveChecker ++;
	  m_Tab->removeTab(index);
  }
}

void Widget::lineLoad()
{
	QString fileName = m_FileName->text();
	QFile file(fileName);

	if (fileName.isEmpty()) {
		return;
	} else {
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}
		QTextStream in(&file);
		g_textedit_map[m_Tab->currentWidget()]->setPlainText(in.readAll());
		m_FileName->setText(fileName);
		g_filename_map[m_Tab->currentWidget()] = fileName;
	}
}

void Widget::buttonSave()
{
	QString save_data;
	save_data = g_textedit_map[m_Tab->currentWidget()]->toPlainText();

	QString fileName = QFileDialog::getSaveFileName(this,
			tr("Save to File"), "",
			tr("all (*)"));
	QFile file(fileName);

	if (fileName.isEmpty()) {
		return;
	} else {
		if (!file.open(QIODevice::WriteOnly)) {
			return;
		}
		QTextStream out(&file);
		out << save_data;
	}
}

void Widget::buttonLoad()
{
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Load from File"), "",
			tr("all (*)"));
	QFile file(fileName);

	if (fileName.isEmpty()) {
		return;
	} else {
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}
		QTextStream in(&file);
		g_textedit_map[m_Tab->currentWidget()]->setPlainText(in.readAll());
		m_FileName->setText(fileName);
		g_filename_map[m_Tab->currentWidget()] = fileName;
	}
}

int Widget::filenameChange(int index)
{
	m_FileName->setText(g_filename_map[m_Tab->currentWidget()]);
	return index;
}

void Widget::settingClickedSlot()
{
	emit settingClickedSignal();
}

void Widget::textCursorPositionChangedSlot1(int)
{
	emit textCursorPositionChangedSignal();
}

void Widget::textCursorPositionChangedSlot2()
{
	emit textCursorPositionChangedSignal();
}

int Widget::getTextCursorLine()
{
	return g_textedit_map[m_Tab->widget(m_Tab->currentIndex())]->textCursor().blockNumber();
}

int Widget::getTextCursorColumn()
{
	return g_textedit_map[m_Tab->widget(m_Tab->currentIndex())]->textCursor().columnNumber();
}

void Widget::cmdExecSlot()
{
	QString cmd;
	cmd = m_CmdLine->text();
	proc->start(cmd);
	g_textedit_map[m_Tab->currentWidget()]->append( ">>>" + cmd );
	std::cout << "command exec." << std::endl;
	m_CmdLine->clear();
}

void Widget::appendViewSlot()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString str(codec->toUnicode(proc->readAllStandardOutput()));
	g_textedit_map[m_Tab->currentWidget()]->append( str );
	g_textedit_map[m_Tab->currentWidget()]->append( "------------------" );
}
