#include "soeditor.hpp"
using namespace std;


	Widget::Widget(QWidget * iParent, Qt::WindowFlags iFlags)
: QWidget(iParent, iFlags)
{
	k_Mode = OFF;
	k_proc = new QProcess(this);
	connect(k_proc, SIGNAL(readyReadStandardOutput()), this, SLOT(appendKnhScriptSlot()));
	keyBind = new SOEKeyBind();
	tabRemoveChecker = 0;

	fontname = "Monospace";
	fontsize = 12;
	setFont(QFont(fontname, fontsize));

	makeWidgets();
}

void Widget::makeWidgets()
{
	countTab = 0;

	CtrlK = new QAction(this);
	CtrlK->setShortcut(tr("Ctrl+K"));

	//Make File Area
	m_FileLabel = new QLabel(tr("File :"));
	m_FileName = new QLineEdit(this);
	m_FileName->setMaxLength(LINE_SIZE);
	m_SaveButton = new QPushButton(tr("&Save"));
	connect(m_SaveButton, SIGNAL(clicked()), this, SLOT(buttonSave()));
	m_LoadButton = new QPushButton(tr("&Load"));
	connect(m_LoadButton, SIGNAL(clicked()), this, SLOT(buttonLoad()));
	m_SettingButton = new QPushButton(tr("&Setting"));
	//
 //Make Setting Menu Area
	menuAreaWidget = new SOEMenuAreaWidget();
	connect(menuAreaWidget, SIGNAL(charSizeChanged(int)), this, SLOT(changeFontSize(int)));
	connect(menuAreaWidget, SIGNAL(charFontChanged(QString)), this, SLOT(changeFontName(QString)));
	connect(menuAreaWidget, SIGNAL(fileMenuViewChanged(int)), this, SLOT(filemenuViewer(int)));
	connect(menuAreaWidget, SIGNAL(subTextViewChanged(int)), this, SLOT(subtextViewer(int)));
	//


  //Make Main Text Area
	m_Tab = new QTabWidget(this);
	m_Tab->setTabShape(QTabWidget::Triangular);
	m_Tab->setUsesScrollButtons(true);
	m_Tab->setMovable(true);
	m_Tab->setTabsClosable(true);
	m_Tab->setDocumentMode(true);


	m_AddTab = new QToolButton();
	m_AddTab->setCursor(Qt::ArrowCursor);
	m_AddTab->setAutoRaise(true);
	m_AddTab->setIcon(QIcon("image/plus_icon.png"));

	m_AllowTab = new QToolButton();
	m_AllowTab->setCursor(Qt::ArrowCursor);
	m_AllowTab->setAutoRaise(true);

	QHBoxLayout *iconLayout = new QHBoxLayout;
	iconLayout->addWidget(m_AllowTab);
	iconLayout->addWidget(m_AddTab);
	iconLayout->setMargin(0);
	iconLayout->setSpacing(0);
	QWidget *iconWidget = new QWidget();
	iconWidget->setLayout(iconLayout);
	m_Tab->setCornerWidget(iconWidget, Qt::TopLeftCorner);
	//

  //Make Sub Text Area
	subTextAreaWidget = new SOESubTextAreaWidget();
	//


  //Set Layout
	m_StatusLayout = new QHBoxLayout();
	m_StatusLayout->addWidget(m_FileLabel);
	m_StatusLayout->addWidget(m_FileName);
	m_StatusLayout->addWidget(m_SaveButton);
	m_StatusLayout->addWidget(m_LoadButton);
	m_StatusLayout->addWidget(m_SettingButton);
	fileMenuWidget = new QWidget();
	fileMenuWidget->setLayout(m_StatusLayout);

	m_TextLayout = new QHBoxLayout();
	m_TextLayout->addWidget(m_Tab);
	m_TextLayout->addWidget(subTextAreaWidget);
	m_TextLayout->setStretch ( 0, 2);

	m_WholeLayout = new QVBoxLayout;
	m_WholeLayout->addWidget(fileMenuWidget);
	m_WholeLayout->addLayout(m_TextLayout);

	m_WholeLayout2 = new QHBoxLayout();
	m_WholeLayout2->addWidget(menuAreaWidget);
	m_WholeLayout2->addLayout(m_WholeLayout);
	setLayout(m_WholeLayout2);
	//
	setSettingMenuArea();
	newTab();

	connect(m_FileName, SIGNAL(returnPressed()), this, SLOT(lineLoad()));
	connect(m_AddTab, SIGNAL(clicked()), this, SLOT(newTab()));
	connect(m_AllowTab, SIGNAL(clicked()), this, SLOT(setSettingMenuArea()));
	connect(m_Tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
	connect(m_Tab, SIGNAL(currentChanged(int)), this, SLOT(filenameChange(int)));
	connect(m_Tab, SIGNAL(currentChanged(int)), this, SLOT(textCursorPositionChangedSlot1(int)));
	connect(m_Tab, SIGNAL(currentChanged(int)), this, SLOT(currentTabChangedSlot(int)));
	connect(keyBind, SIGNAL(CtrlF_PressedSignal()), this, SLOT(setCtrlF()));
	connect(keyBind, SIGNAL(CtrlB_PressedSignal()), this, SLOT(setCtrlB()));
	connect(keyBind, SIGNAL(CtrlN_PressedSignal()), this, SLOT(setCtrlN()));
	connect(keyBind, SIGNAL(CtrlP_PressedSignal()), this, SLOT(setCtrlP()));
	connect(CtrlK, SIGNAL(triggered()), this, SLOT(konohaMode()));
}
void Widget::filemenuViewer(int i)
{
	if (i == Qt::Unchecked){
		fileMenuWidget->hide();
	}
	if (i == Qt::Checked){
		fileMenuWidget->show();
	}
}
void Widget::subtextViewer(int i)
{
	if (i == Qt::Unchecked){
		subTextAreaWidget->hide();
	}
	if (i == Qt::Checked){
		subTextAreaWidget->show();
	}
}

void Widget::newTab()
{
	countTab ++;
	QString title = tr("new text field") + QString::number(countTab);
	m_Text = new SoTextEdit();
	keyBind->setSOE_TextKeyBind(m_Text);
	m_Tab->addTab(m_Text, title);
	QTextCursor t_cursor = m_Text->textCursor();
	t_cursor.movePosition(QTextCursor::End);
	m_Text->setTextCursor(t_cursor);
	m_Text->setFont(QFont(fontname, fontsize));
	m_Text->addAction(CtrlK);

	m_textedit_map.insert(map<QWidget*, SoTextEdit*>::value_type(m_Tab->widget(m_Tab->count() - 1), m_Text));
	m_filename_map.insert(map<QWidget*, QString>::value_type(m_Tab->widget(m_Tab->count() - 1), title));
	m_FileName->setText(title);
	connect(m_Text, SIGNAL(cursorPositionChanged()), this, SLOT(textCursorPositionChangedSlot2()));
	connect(m_Text, SIGNAL(returnPressed()), this, SLOT(konohaRead()));
	m_Tab->setCurrentIndex(m_Tab->count() - 1);
}

void Widget::closeTab(int index)
{
	if(countTab > (tabRemoveChecker + 1))
	{
	  m_textedit_map.erase(m_Tab->widget(index));
	  m_filename_map.erase(m_Tab->widget(index));
	  tabRemoveChecker ++;
	  m_Tab->removeTab(index);
  }
}

void Widget::setSettingMenuArea()
{
	if (settingMenu == OFF){
		m_AllowTab->setIcon(QIcon("image/rightallow.png"));
		menuAreaWidget->hide();
		settingMenu = ON;
	}
	else {
		m_AllowTab->setIcon(QIcon("image/leftallow.png"));
		menuAreaWidget->show();
		settingMenu = OFF;
	}
}

void Widget::lineLoad()
{
	QString fileName = m_FileName->text();
	if (fileName.isEmpty()) {
		return;
	}   
	else {
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}
		QTextStream in(&file);
		m_FileName->setText(fileName);
		m_textedit_map[m_Tab->currentWidget()]->setPlainText(in.readAll());
		m_filename_map[m_Tab->currentWidget()] = fileName;
	}
}

void Widget::buttonSave()
{
	QString save_data;
	save_data = m_textedit_map[m_Tab->currentWidget()]->toPlainText();

	QString fileName = QFileDialog::getSaveFileName(this,
			tr("Save to File"), "",
			tr("all (*)"));

	if (fileName.isEmpty()) {
		return;
	} else {
		QFile file(fileName);
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
		newTab();
		m_textedit_map[m_Tab->currentWidget()]->setPlainText(in.readAll());
		m_FileName->setText(fileName);
		m_filename_map[m_Tab->currentWidget()] = fileName;

		QString tab_title = (fileName.split("/", QString::SkipEmptyParts)).back();
		m_Tab->setTabText(m_Tab->currentIndex(), tab_title);
	}
}

int Widget::filenameChange(int index)
{
	m_FileName->setText(m_filename_map[m_Tab->currentWidget()]);
	return index;
}

void Widget::settingClickedSlot()
{
	emit settingClickedSignal();
}

void Widget::changeFontSize(int t)
{
	int i;
	fontsize = t;
	for(i = 0; i < countTab; i ++){
		if(m_textedit_map[m_Tab->widget(i)] != NULL)
			m_textedit_map[m_Tab->widget(i)]->setFont(QFont(fontname, fontsize));
	}
}

void Widget::changeFontName(QString str)
{
	int i;
	fontname = str;
	for(i = 0; i < countTab; i ++){
		if(m_textedit_map[m_Tab->widget(i)] != NULL)
			m_textedit_map[m_Tab->widget(i)]->setFont(QFont(fontname, fontsize));
	}
}

void Widget::konohaMode()
{

	if (k_Mode == OFF){
		k_Mode = ON;
		//m_textedit_map[m_Tab->currentWidget()]->setKonohaMode(k_Mode);
		printf("KonohaMode Started\n");
		m_textedit_map[m_Tab->currentWidget()]->appendPlainText("/*------ start konoha mode ------*/");
		m_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
		m_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
		k_proc->setReadChannelMode(QProcess::MergedChannels);
		k_proc->setReadChannel(QProcess::StandardOutput);
		k_proc->start("konoha");
	}
	else {
		k_Mode = OFF;
		k_proc->terminate();
		printf("KonohaMode Finished\n");
		m_textedit_map[m_Tab->currentWidget()]->appendPlainText("/*------ finish konoha mode ------*/");
	}
}

void Widget::konohaRead()
{
	if (k_Mode == ON){
		QTextCursor cr;
		cr = m_textedit_map[m_Tab->currentWidget()]->textCursor();
		cr.deletePreviousChar();
		cr.movePosition(QTextCursor::Up, QTextCursor::KeepAnchor);
		cr.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
		cr.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);

		QString kScript = cr.selectedText();
		QRegExp pattern(">>>");
		kScript = kScript.replace(pattern, "");
		kScript = kScript.simplified();
		k_proc->write(qPrintable(kScript));
		k_proc->write("\r\n");

		printf("%s\n",qPrintable(kScript));
	}
}
void Widget::appendKnhScriptSlot()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString str(codec->toUnicode(k_proc->readAll()));
	m_textedit_map[m_Tab->currentWidget()]->appendPlainText( str );
}

void Widget::konohaEval()
{
}

void Widget::setCtrlF()
{
	m_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Right, QTextCursor::MoveAnchor);
}
void Widget::setCtrlB()
{
	m_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);
}
void Widget::setCtrlP()
{
	m_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Up, QTextCursor::MoveAnchor);
}
void Widget::setCtrlN()
{
	m_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
}

void Widget::textCursorPositionChangedSlot1(int i /*UNUSED*/)
{
	i = i;
	emit textCursorPositionChangedSignal();
}

void Widget::textCursorPositionChangedSlot2()
{
	emit textCursorPositionChangedSignal();
}

int Widget::getTextCursorLine()
{
	return m_textedit_map[m_Tab->widget(m_Tab->currentIndex())]->textCursor().blockNumber();
}

int Widget::getTextCursorColumn()
{
	return m_textedit_map[m_Tab->widget(m_Tab->currentIndex())]->textCursor().columnNumber();
}

void Widget::currentTabChangedSlot(int t)
{
	emit currentTabChangedSignal(t);
}
