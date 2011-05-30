#ifndef Widget_H
#define Widget_H
#include <QWidget>
#include <QtGui>
#include <list>
#include <qstring.h>
#include <string>
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <iostream>
#include <list>
#include <readline/history.h>
#include "Window.h"
#include "SOEKeyBind.h"
#include "sotextedit.h"
#define LINE_SIZE 64

class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QLineEdit;
class QTextEdit;
class QTextBlock;
class QTextCursor;
class QPushButton;
class QToolButton;
class QTabWidget;
class QAction;
class QListWidget;
class QColor;
class QPallete;
class QFont;
class QTextCodec;
class QProcess;
class SOEKeyBind;

extern std::map<QWidget*, SoTextEdit*> g_textedit_map;
extern std::map<QWidget*, QString> g_filename_map;

class Widget : public QWidget
{
	Q_OBJECT
	public:
		Widget(QWidget * iParent = 0, Qt::WindowFlags iFlags = 0);
		int getTextCursorLine();
		int getTextCursorColumn();
	signals :
		void settingClickedSignal();
		void textCursorPositionChangedSignal();//new
	protected slots :
		void newTab();
		void closeTab(int index);
		void textChecker();
		void lineLoad();
		void buttonLoad();
		void buttonSave();
		int filenameChange(int);
		void cmdExecSlot();
		void appendViewSlot();
		void settingClickedSlot();
		void setCtrlF();
		void setCtrlB();
		void setCtrlP();
		void setCtrlN();
		void textCursorPositionChangedSlot1(int p);//new
		void textCursorPositionChangedSlot2();//new
	private:
		void makeWidgets();
		int countTab;
		int tabRemoveChecker;

		QHBoxLayout *m_h_StatusLayout;
		QHBoxLayout *m_s_CmdLayout;
		QHBoxLayout *m_c_TextLayout;
		QVBoxLayout *m_v_WholeLayout;

		QLabel *m_FileLabel;
		QLineEdit *m_FileName;
		QPushButton *m_SaveButton;
		QPushButton *m_LoadButton;
		QPushButton *m_SettingButton;

		QLabel *m_CmdLabel;
		QLineEdit *m_CmdLine;

		QTabWidget *m_Tab;
		QToolButton *m_AddTab;

		SoTextEdit *m_Text;

		QAction *m_AddTabAction;
		
		QProcess *proc;
		
		SOEKeyBind *keyBind;
};
#endif 
