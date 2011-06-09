#include "soeditor.h"

using namespace std;


	Widget::Widget(QWidget * iParent, Qt::WindowFlags iFlags)
: QWidget(iParent, iFlags)
{
	k_Mode = OFF;
	proc = new QProcess(this);
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
	m_SettingCharGroup = new QGroupBox("Set Char");
	QVBoxLayout *settingCharGroupLayout = new QVBoxLayout;
	settingMenu = OFF;
	settingCharSizeLabel = new QLabel(tr("Size:"));
	settingCharSizeSpinBox = new QSpinBox();
	settingCharSizeSpinBox->setRange(0, 64);

	QHBoxLayout *settingCharSizeLayout = new QHBoxLayout();
	settingCharSizeLayout->addWidget(settingCharSizeLabel);
	settingCharSizeLayout->addWidget(settingCharSizeSpinBox);
	settingFontLabel = new QLabel(tr("Font:"));
	settingFontBox = new QComboBox();
	settingFontBox->addItem("Arial");
	settingFontBox->addItem("Impact");
	settingFontBox->addItem("Serif");
	settingFontBox->addItem("Monospace");

	QHBoxLayout *settingFontLayout = new QHBoxLayout();
	settingFontLayout->addWidget(settingFontLabel);
	settingFontLayout->addWidget(settingFontBox);
	settingCharGroupLayout->addLayout(settingCharSizeLayout);
	settingCharGroupLayout->addLayout(settingFontLayout);
	m_SettingCharGroup->setLayout(settingCharGroupLayout);

	m_SettingBGGroup = new QGroupBox("Set Background");

	m_SettingDisplayGroup = new QGroupBox("Set Display Area");
	QCheckBox *fileBox  = new QCheckBox("File Menu Area");
	QCheckBox *subtextBox  = new QCheckBox("Sub Text Area");
	QVBoxLayout *areaBoxLayout = new QVBoxLayout;
	fileBox->setChecked (true);
	subtextBox->setChecked (true);
	areaBoxLayout->addWidget(fileBox);
	areaBoxLayout->addWidget(subtextBox);
	m_SettingDisplayGroup->setLayout(areaBoxLayout);
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
	m_CmdLabel = new QLabel(tr("Cmd:"));
	m_CmdLine = new QLineEdit(this);
	m_SubText = new SoTextEdit();
	m_SubText->setCursorWidth(6);
	m_SubText->ensureCursorVisible();
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

	m_CmdLayout = new QHBoxLayout();
	m_CmdLayout->addWidget(m_CmdLabel);
	m_CmdLayout->addWidget(m_CmdLine);

	m_SubTextLayout = new QVBoxLayout();
	m_SubTextLayout->addLayout(m_CmdLayout);
	m_SubTextLayout->addWidget(m_SubText);
	subTextWidget = new QWidget();
	subTextWidget->setLayout(m_SubTextLayout);

	m_TextLayout = new QHBoxLayout();
	m_TextLayout->addWidget(m_Tab);
	m_TextLayout->addWidget(subTextWidget);
	m_TextLayout->setStretch ( 0, 2);

	m_WholeLayout = new QVBoxLayout;
	m_WholeLayout->addWidget(fileMenuWidget);
	m_WholeLayout->addLayout(m_TextLayout);

	m_SettingMenuLayout = new QVBoxLayout();
	m_SettingMenuLayout->addWidget(m_SettingCharGroup);
	m_SettingMenuLayout->addWidget(m_SettingBGGroup);
	m_SettingMenuLayout->addWidget(m_SettingDisplayGroup);
	settingMenuWidget = new QWidget();
	settingMenuWidget->setLayout(m_SettingMenuLayout);

	QPalette basicalWidgetPalette;
	basicalWidgetPalette.setColor(QPalette::Background, Qt::white);

	settingMenuWidget->setPalette(basicalWidgetPalette);
	settingMenuWidget->setAutoFillBackground(true);

	m_WholeLayout2 = new QHBoxLayout();
	m_WholeLayout2->addWidget(settingMenuWidget);
	m_WholeLayout2->addLayout(m_WholeLayout);
	setLayout(m_WholeLayout2);
	//
	setSettingMenuArea();
	newTab();

	connect(m_FileName, SIGNAL(returnPressed()), this, SLOT(lineLoad()));
	connect(settingCharSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(changeFontSize(int)));
	connect(settingFontBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeFontName(QString)));
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
		subTextWidget->hide();
	}
	if (i == Qt::Checked){
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
		settingMenuWidget->hide();
		settingMenu = ON;
	}
	else {
		m_AllowTab->setIcon(QIcon("image/leftallow.png"));
		settingMenuWidget->show();
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
		m_textedit_map[m_Tab->currentWidget()]->setKonohaMode(k_Mode);
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
