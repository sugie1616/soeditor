#include "soeditor.hpp"

SOESubTextAreaWidget::SOESubTextAreaWidget() : QWidget()
{
	makeSubTextAreaWidget();
}

void SOESubTextAreaWidget::makeSubTextAreaWidget()
{
	proc = new QProcess(this);
	connect(proc, SIGNAL(readyReadStandardOutput()), this, SLOT(appendViewSlot()));

	cmdLabel = new QLabel(tr("Cmd:"));
	cmdLine = new QLineEdit(this);
	connect(cmdLine, SIGNAL(returnPressed()), this, SLOT(cmdExecSlot()));

	subText = new SoTextEdit();

	cmdLayout = new QHBoxLayout();
	cmdLayout->addWidget(cmdLabel);
	cmdLayout->addWidget(cmdLine);

	subTextAreaLayout = new QVBoxLayout();
	subTextAreaLayout->addLayout(cmdLayout);
	subTextAreaLayout->addWidget(subText);
	setLayout(subTextAreaLayout);
}

void SOESubTextAreaWidget::cmdExecSlot()
{
	QString cmd;
	cmd = cmdLine->text();
	if (cmd != "konoha" && cmd != "rst"){
		proc->start(cmd);
		subText->appendPlainText( ">>>" + cmd );
		std::cout << "command exec." << std::endl;
		cmdLine->clear();
	}
	if (cmd == "rst"){
		std::cout << "command exec." << std::endl;
		cmdLine->clear();
		subText->setPlainText("");
	}
	else {
		cmdLine->clear();
	}
}

void SOESubTextAreaWidget::appendViewSlot()
{
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString str(codec->toUnicode(proc->readAllStandardOutput()));
	subText->appendPlainText( str );
	subText->appendPlainText( "------------------" );
}

