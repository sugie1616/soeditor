#include "soeditor.h"

SOEKeyBind::SOEKeyBind(QObject *parent):QAction(parent)
{
}

/*void SOEKeyBind::setSOE_MainWidgetKeyBind(QWidget *widget)
{
	QAction *CtrlC = new QAction(this);
	CtrlC->setShortcut(tr("Ctrl+C"));
	connect(CtrlC, SIGNAL(triggered()), this, SLOT(CtrlC_PressedSlot()));
	widget->addAction(CtrlC);
}
*/
void SOEKeyBind::setSOE_TextKeyBind(QTextEdit *text)
{
	QAction *CtrlF = new QAction(this);
	CtrlF->setShortcut(tr("Ctrl+F"));
	connect(CtrlF, SIGNAL(triggered()), this, SLOT(CtrlF_PressedSlot()));
	text->addAction(CtrlF);
	QAction *CtrlB = new QAction(this);
	CtrlB->setShortcut(tr("Ctrl+B"));
	connect(CtrlB, SIGNAL(triggered()), this, SLOT(CtrlB_PressedSlot()));
	text->addAction(CtrlB);
	QAction *CtrlN = new QAction(this);
	CtrlN->setShortcut(tr("Ctrl+N"));
	connect(CtrlN, SIGNAL(triggered()), this, SLOT(CtrlN_PressedSlot()));
	text->addAction(CtrlN);
	QAction *CtrlP = new QAction(this);
	CtrlP->setShortcut(tr("Ctrl+P"));
	connect(CtrlP, SIGNAL(triggered()), this, SLOT(CtrlP_PressedSlot()));
	text->addAction(CtrlP);
}

void SOEKeyBind::setSOE_WindowKeyBind(QMainWindow *window)
{
	QAction *CtrlQ = new QAction(this);
	CtrlQ->setShortcut(tr("Ctrl+Q"));
	connect(CtrlQ, SIGNAL(triggered()), this, SLOT(CtrlQ_PressedSlot()));
	window->addAction(CtrlQ);
}

void SOEKeyBind::CtrlF_PressedSlot()
{
	emit CtrlF_PressedSignal();
}
void SOEKeyBind::CtrlB_PressedSlot()
{
	emit CtrlB_PressedSignal();
}
void SOEKeyBind::CtrlN_PressedSlot()
{
	emit CtrlN_PressedSignal();
}
void SOEKeyBind::CtrlP_PressedSlot()
{
	emit CtrlP_PressedSignal();
}

void SOEKeyBind::CtrlQ_PressedSlot()
{
	emit CtrlQ_PressedSignal();
}
