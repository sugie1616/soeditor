#include "soeditor.h"

using namespace std;

map<QWidget*, SoTextEdit*> g_textedit_map;
map<QWidget*, QString> g_filename_map;

	Widget::Widget(QWidget * iParent, Qt::WindowFlags iFlags)
: QWidget(iParent, iFlags)
{
	k_Mode = OFF;
	proc = new QProcess(this);
	keyBind = new SOEKeyBind();
	QFile kTmpFile("tmp.k");
	tabRemoveChecker = 0;

	fontname = "Monospace";
	fontsize = 12;
	setFont(QFont(fontname, fontsize));

	makeWidgets();
}

void Widget::makeWidgets()
{
	countTab = 0;

	k_proc = new QProcess(this);
	CtrlK = new QAction(this);
	CtrlK->setShortcut(tr("Ctrl+K"));

	//for save&load
	m_FileLabel = new QLabel(tr("File :"));
	m_FileName = new QLineEdit(this);
	m_FileName->setMaxLength(LINE_SIZE);
	m_SaveButton = new QPushButton(tr("&Save"));
	m_LoadButton = new QPushButton(tr("&Load"));
	m_SettingButton = new QPushButton(tr("&Setting"));
	//


  //Main Text Area
	m_Tab = new QTabWidget(this);
	m_Tab->setTabShape(QTabWidget::Triangular);
	m_Tab->setUsesScrollButtons(true);
	m_Tab->setMovable(true);
	m_Tab->setTabsClosable(true);
	m_Tab->setDocumentMode(true);

	QHBoxLayout *iconLayout = new QHBoxLayout;
	QWidget *iconWidget = new QWidget();


	m_AddTab = new QToolButton();
	m_AddTab->setCursor(Qt::ArrowCursor);
	m_AddTab->setAutoRaise(true);
	m_AddTab->setIcon(QIcon("image/plus_icon.png"));

	m_AllowTab = new QToolButton();
	m_AllowTab->setCursor(Qt::ArrowCursor);
	m_AllowTab->setAutoRaise(true);

	iconLayout->addWidget(m_AllowTab);
	iconLayout->addWidget(m_AddTab);
	iconLayout->setMargin(0);
	iconLayout->setSpacing(0);
	iconWidget->setLayout(iconLayout);
	m_Tab->setCornerWidget(iconWidget, Qt::TopLeftCorner);
	//

  //Sub Text Area
	m_CmdLabel = new QLabel(tr("Cmd:"));
	m_CmdLine = new QLineEdit(this);
	m_SubText = new SoTextEdit();
	m_SubText->setCursorWidth(6);
	m_SubText->ensureCursorVisible();
	//

  //Setting Menu Area
	m_SetCharGroup = new QGroupBox("Set Char");
	QVBoxLayout *setCharGroupLayout = new QVBoxLayout;
	settingmenu = OFF;
	setCharSizeLabel = new QLabel(tr("Size:"));
	setCharSizeSpinBox = new QSpinBox;
	setCharSizeSpinBox->setRange(0, 64);
	QHBoxLayout *setCharSizeLayout = new QHBoxLayout;
	setCharSizeLayout->addWidget(setCharSizeLabel);
	setCharSizeLayout->addWidget(setCharSizeSpinBox);
	setFontLabel = new QLabel(tr("Font:"));
	setFontBox = new QComboBox;
	setFontBox->addItem("Arial");
	setFontBox->addItem("Impact");
	setFontBox->addItem("Serif");
	setFontBox->addItem("Monospace");
	QHBoxLayout *setFontLayout = new QHBoxLayout;
	setFontLayout->addWidget(setFontLabel);
	setFontLayout->addWidget(setFontBox);
	setCharGroupLayout->addLayout(setCharSizeLayout);
	setCharGroupLayout->addLayout(setFontLayout);
	m_SetCharGroup->setLayout(setCharGroupLayout);

	m_SetBGGroup = new QGroupBox("Set Background");

	m_SetDisplayGroup = new QGroupBox("Set Display Area");
	QCheckBox *fileBox  = new QCheckBox("File Menu Area");
	QCheckBox *subtextBox  = new QCheckBox("Sub Text Area");
	QVBoxLayout *areaBoxLayout = new QVBoxLayout;
	fileBox->setChecked (true);
	subtextBox->setChecked (true);
	areaBoxLayout->addWidget(fileBox);
	areaBoxLayout->addWidget(subtextBox);
	m_SetDisplayGroup->setLayout(areaBoxLayout);
	//

  //Set Layout
	m_h_StatusLayout = new QHBoxLayout();
	m_h_StatusLayout->addWidget(m_FileLabel);
	m_h_StatusLayout->addWidget(m_FileName);
	m_h_StatusLayout->addWidget(m_SaveButton);
	m_h_StatusLayout->addWidget(m_LoadButton);
	m_h_StatusLayout->addWidget(m_SettingButton);
	fileMenuWidget = new QWidget();
	fileMenuWidget->setLayout(m_h_StatusLayout);

	m_s_CmdLayout = new QHBoxLayout();
	m_s_CmdLayout->addWidget(m_CmdLabel);
	m_s_CmdLayout->addWidget(m_CmdLine);

	m_r_SubTextLayout = new QVBoxLayout();
	m_r_SubTextLayout->addLayout(m_s_CmdLayout);
	m_r_SubTextLayout->addWidget(m_SubText);
	subTextWidget = new QWidget();
	subTextWidget->setLayout(m_r_SubTextLayout);

	m_c_TextLayout = new QHBoxLayout();
	m_c_TextLayout->addWidget(m_Tab);
	m_c_TextLayout->addWidget(subTextWidget);
	m_c_TextLayout->setStretch ( 0, 2);

	m_v_WholeLayout = new QVBoxLayout;
	m_v_WholeLayout->addWidget(fileMenuWidget);
	m_v_WholeLayout->addLayout(m_c_TextLayout);

	m_l_SettingMenuLayout = new QVBoxLayout();
	m_l_SettingMenuLayout->addWidget(m_SetCharGroup);
	m_l_SettingMenuLayout->addWidget(m_SetBGGroup);
	m_l_SettingMenuLayout->addWidget(m_SetDisplayGroup);
	settingMenuWidget = new QWidget();
	settingMenuWidget->setLayout(m_l_SettingMenuLayout);

	QPalette basicalWidgetPalette;
	basicalWidgetPalette.setColor(QPalette::Background, Qt::white);

	settingMenuWidget->setPalette(basicalWidgetPalette);
	settingMenuWidget->setAutoFillBackground(true);

	m_v2_WholeLayout = new QHBoxLayout();
	m_v2_WholeLayout->addWidget(settingMenuWidget);
	m_v2_WholeLayout->addLayout(m_v_WholeLayout);
	setLayout(m_v2_WholeLayout);
	//
	setSettingMenuArea();
	newTab();

	connect(m_FileName, SIGNAL(returnPressed()), this, SLOT(lineLoad()));
	connect(m_SaveButton, SIGNAL(clicked()), this, SLOT(buttonSave()));
	connect(m_LoadButton, SIGNAL(clicked()), this, SLOT(buttonLoad()));
	connect(setCharSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeFontSize(int)));
	connect(setFontBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeFontName(QString)));
	connect(fileBox, SIGNAL(stateChanged(int)), this, SLOT(filemenuViewer(int)));
	connect(subtextBox, SIGNAL(stateChanged(int)), this, SLOT(subtextViewer(int)));
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
	connect(m_CmdLine, SIGNAL(returnPressed()), this, SLOT(cmdExecSlot()));
	connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(appendViewSlot()));
}
void Widget::filemenuViewer(int i)
{
	if (i == 0){
		fileMenuWidget->hide();
	}
	if (i == 2){
		fileMenuWidget->show();
	}
}
void Widget::subtextViewer(int i)
{
	if (i == 0){
		subTextWidget->hide();
	}
	if (i == 2){
		subTextWidget->show();
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

	g_textedit_map.insert(map<QWidget*, SoTextEdit*>::value_type(m_Tab->widget(m_Tab->count() - 1), m_Text));
	g_filename_map.insert(map<QWidget*, QString>::value_type(m_Tab->widget(m_Tab->count() - 1), title));
	m_FileName->setText(title);
	connect(m_Text, SIGNAL(cursorPositionChanged()), this, SLOT(textCursorPositionChangedSlot2()));
	connect(m_Text, SIGNAL(returnPressed()), this, SLOT(konohaRead()));
	m_Tab->setCurrentIndex(m_Tab->count() - 1);
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
void Widget::setSettingMenuArea()
{
	if (settingmenu == OFF){
		m_AllowTab->setIcon(QIcon("image/rightallow.png"));
		settingMenuWidget->hide();
		settingmenu = ON;
	}
	else {
		m_AllowTab->setIcon(QIcon("image/leftallow.png"));
		settingMenuWidget->show();
		settingmenu = OFF;
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
		newTab();
		g_textedit_map[m_Tab->currentWidget()]->setPlainText(in.readAll());
		m_FileName->setText(fileName);
		g_filename_map[m_Tab->currentWidget()] = fileName;

		QString tab_title = (fileName.split("/", QString::SkipEmptyParts)).back();
		m_Tab->setTabText(m_Tab->currentIndex(), tab_title);


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


void Widget::cmdExecSlot()
{
	QString cmd;
	cmd = m_CmdLine->text();
	if (cmd != "konoha" && cmd != "rst"){
		proc->start(cmd);
		m_SubText->appendPlainText( ">>>" + cmd );
		std::cout << "command exec." << std::endl;
		m_CmdLine->clear();
	}
	if (cmd == "rst"){
		std::cout << "command exec." << std::endl;
		m_CmdLine->clear();
		m_SubText->setPlainText("");
	}
	else {
		m_CmdLine->clear();
	}
}

void Widget::appendViewSlot()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString str(codec->toUnicode(proc->readAllStandardOutput()));
	m_SubText->appendPlainText( str );
	m_SubText->appendPlainText( "------------------" );
}

void Widget::changeFontSize(int t)
{
	int i;
	fontsize = t;
	for(i = 0; i < countTab; i ++){
		if(g_textedit_map[m_Tab->widget(i)] != NULL)
			g_textedit_map[m_Tab->widget(i)]->setFont(QFont(fontname, fontsize));
	}
}

void Widget::changeFontName(QString str)
{
	int i;
	fontname = str;
	for(i = 0; i < countTab; i ++){
		if(g_textedit_map[m_Tab->widget(i)] != NULL)
			g_textedit_map[m_Tab->widget(i)]->setFont(QFont(fontname, fontsize));
	}
}

void Widget::konohaMode()
{
	if (k_Mode == OFF){
		k_Mode = ON;
		printf("KonohaMode Start\n");
		g_textedit_map[m_Tab->currentWidget()]->appendPlainText("/*------ start konoha mode ------*/");
		g_textedit_map[m_Tab->currentWidget()]->appendPlainText(">>> ");
		g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
		QString program("Konoha");
		k_proc->start(program);
	}
	else {
		k_Mode = OFF;
		k_proc->terminate();
		g_textedit_map[m_Tab->currentWidget()]->appendPlainText("/*------ finish konoha mode ------*/");
	}
}

void Widget::konohaRead()
{
	if (k_Mode == ON){
		QTextCursor cr;
		cr = g_textedit_map[m_Tab->currentWidget()]->textCursor();
		cr.deletePreviousChar();
		cr.movePosition(QTextCursor::Up, QTextCursor::KeepAnchor);
		cr.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
		cr.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		QString outbuf = cr.selectedText();
		outbuf[0] = ' ';
		outbuf[1] = ' ';
		outbuf[2] = ' ';
		outbuf[3] = ' ';

		printf("%s\n",qPrintable(outbuf));
		g_textedit_map[m_Tab->currentWidget()]->appendPlainText(">>> ");
		g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::Down, QTextCursor::MoveAnchor);
		g_textedit_map[m_Tab->currentWidget()]->moveCursor(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
	}
}

void Widget::konohaEval()
{
}

void Widget::appendKonohaEvaled()
{
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

void Widget::currentTabChangedSlot(int t)
{
	emit currentTabChangedSignal(t);
}
