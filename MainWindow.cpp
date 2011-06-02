#include "soeditor.h"

MainWindow::MainWindow(QWidget * iParent, Qt::WindowFlags iFlags) : QMainWindow(iParent, iFlags)
{
	countBG = 0;
	cursorline = 1;
	cursorcolumn = 1;

	timeLabel = new QLabel(this);
	cursorPositionLabel = new QLabel(this);
	tabNumLabel = new QLabel(this);

	cursorPositionLabel->setText(QString("line:1 column:2"));

	statusBar()->addPermanentWidget(cursorPositionLabel, 0);
	statusBar()->addPermanentWidget(tabNumLabel, 0);
	statusBar()->addPermanentWidget(timeLabel,0);
	tabNumLabel->setText(QString("tab number:1"));

	w_bgImage = QImage("image/screen4.png");

	QPalette palette;
	palette.setBrush(QPalette::Background, w_bgImage);
	setPalette(palette);

	keyBind = new SOEKeyBind();
	keyBind->setSOE_WindowKeyBind(this);
	connect(keyBind, SIGNAL(CtrlQ_PressedSignal()), this, SLOT(close()));
	createTimeStatusBar();
	setCurrentTime();
	m_Widget = new Widget(this);
	connect(m_Widget, SIGNAL(textCursorPositionChangedSignal()), this, SLOT(createTextCursorPositionStatusBar()));
	connect(m_Widget, SIGNAL(settingClickedSignal()), this, SLOT(setWindowBG()));
	connect(m_Widget, SIGNAL(currentTabChangedSignal(int)), this, SLOT(setCurrentTabStatus(int)));
	setAutoFillBackground(true);
	setCentralWidget(m_Widget);
	setWindowTitle(tr("Soeditor"));
	resize(1024,1024);
	show(); 
}

void MainWindow::createTimeStatusBar()
{
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentTime()));
	timer->start(1000);
}

void MainWindow::createTextCursorPositionStatusBar()
{
cursorline = m_Widget->getTextCursorLine();
cursorcolumn = m_Widget->getTextCursorColumn();
cursorPositionLabel->setText(QString("line:%1 column:%2").arg(cursorline + 1).arg(cursorcolumn + 1));
//statusBar()->showMessage(QString("line:%1 column:%2").arg(cursorline + 1).arg(cursorcolumn + 1));
}

void MainWindow::setCurrentTime()
{
	dt = QDateTime::currentDateTime();
	now = dt.toString();
	now[0] = ' ';
	timeLabel->setText(now);
}

void MainWindow::setCurrentTabStatus(int t)
{
	//statusBar()->showMessage(QString("current tab number :%1").arg(t + 1));
	tabNumLabel->setText(QString("tab number:%1").arg(t + 1));
}

void MainWindow::setWindowBG() 
{
	switch (countBG)
	{
	case 0:w_bgImage = QImage("image/screen1.png");
		countBG ++;
		break;
	case 1:w_bgImage = QImage("image/screen.jpg");
		countBG ++;
		break;
	case 2:w_bgImage = QImage("image/screen2.png");
		countBG ++;
		break;
	case 3:w_bgImage = QImage("image/screen4.png");
		countBG ++;
		break;
	default:countBG = 0;setWindowBG();
			break;
}
	palette.setBrush(QPalette::Background, w_bgImage);
	setPalette(palette);
}
