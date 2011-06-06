//#include <konoha1.h>
//#undef T1
//#undef T2
#include <QFrame>
#include <QTextStream>
#include <QtGui>
#include <QWidget>
#include <list>
#include <qstring.h>
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <readline/history.h>

#define LINE_SIZE 64
#define OFF 0
#define ON 1

class SoTextEdit;
class Widget;
class SOEKeyBind;

extern std::map<QWidget*, SoTextEdit*> g_textedit_map;
extern std::map<QWidget*, QString> g_filename_map;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow(QWidget * iParent = 0, Qt::WindowFlags iFlags = 0);
	protected slots:
		void setCurrentTime(); 
		void setWindowBG();
		void createTextCursorPositionStatusBar();
		void setCurrentTabStatus(int t);//
	private:
		void createMenus();
		QMenu *m_FileMenu;
		QMenu *m_ViewMenu;
		int countBG;
		int lineNum;
		int cursorcolumn;
		int cursorline;

		void createTimeStatusBar();
		QPalette *plt;

		QDateTime dt;
		QString now;
		QLabel *timeLabel;
		QLabel *cursorPositionLabel;
		QLabel *tabNumLabel;

		Widget *m_Widget;

		SOEKeyBind *keyBind;

		QPalette palette;
		QImage w_bgImage;
};

class Widget : public QWidget
{
	Q_OBJECT
	public:
		Widget(QWidget * iParent = 0, Qt::WindowFlags iFlags = 0);
		int getTextCursorLine();
		int getTextCursorColumn();
	signals :
		void settingClickedSignal();
		void textCursorPositionChangedSignal();
		void currentTabChangedSignal(int t);
	protected slots :
		void newTab();
		void closeTab(int index);
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
		void textCursorPositionChangedSlot1(int p);
		void textCursorPositionChangedSlot2();
		void currentTabChangedSlot(int t);
		void changeFontSize(int fontsize);
		void changeFontName(QString fontname);
		void setSettingMenuArea();
		void konohaMode();
		void konohaRead();
		void konohaEval();
		void appendKonohaEvaled();
		void filemenuViewer(int i);
		void subtextViewer(int i);
		
	private:
		void makeWidgets();
		int countTab;
		int tabRemoveChecker;
		QString fontname;
		int fontsize;
		int settingmenu;
		int k_Mode;
		QHBoxLayout *m_h_StatusLayout;
		QHBoxLayout *m_s_CmdLayout;
		QHBoxLayout *m_c_TextLayout;
		QVBoxLayout *m_r_SubTextLayout;
		QVBoxLayout *m_v_WholeLayout;
		QVBoxLayout *m_l_SettingMenuLayout;
		QHBoxLayout *m_v2_WholeLayout;

		QLabel *m_FileLabel;
		QLineEdit *m_FileName;
		QPushButton *m_SaveButton;
		QPushButton *m_LoadButton;
		QPushButton *m_SettingButton;
		
		QGroupBox *m_SetCharGroup;
		QLabel *setCharSizeLabel;
		QSpinBox *setCharSizeSpinBox;
		QLabel *setFontLabel;
		QComboBox *setFontBox;
		QGroupBox *m_SetBGGroup;
		QGroupBox *m_SetDisplayGroup;

		QLabel *m_CmdLabel;
		QLineEdit *m_CmdLine;

		QTabWidget *m_Tab;
		QToolButton *m_AddTab;
		QToolButton *m_AllowTab;

		QWidget *settingMenuWidget;
		QWidget *fileMenuWidget;
		QWidget *mainTextWidget;
		QWidget *subTextWidget;

		SoTextEdit *m_Text;
		SoTextEdit *m_SubText;

		QAction *m_AddTabAction;
		QAction *CtrlK;
		
		QProcess *proc;
		QProcess *k_proc;
		
		SOEKeyBind *keyBind;
};

class SOEKeyBind :public QAction
{
	Q_OBJECT

	public:
		SOEKeyBind(QObject *parent = 0);
		//void setSOE_MainWidgetKeyBind(QWidget *widget);
		void setSOE_TextKeyBind(SoTextEdit *text);
		void setSOE_WindowKeyBind(QMainWindow *window);
	signals:
		//void CtrlA_PressedSignal();
		void CtrlB_PressedSignal();
		//void CtrlC_PressedSignal();
		//void CtrlD_PressedSignal();
		//void CtrlE_PressedSignal();
		void CtrlF_PressedSignal();
		//void CtrlG_PressedSignal();
		//void CtrlH_PressedSignal();
		//void CtrlI_PressedSignal();
		//void CtrlJ_PressedSignal();
		//void CtrlK_PressedSignal();
		//void CtrlL_PressedSignal();
		//void CtrlM_PressedSignal();
		void CtrlN_PressedSignal();
		//void CtrlO_PressedSignal();
		void CtrlP_PressedSignal();
		void CtrlQ_PressedSignal();
		//void CtrlR_PressedSignal();
		//void CtrlS_PressedSignal();
		//void CtrlT_PressedSignal();
		//void CtrlU_PressedSignal();
		//void CtrlV_PressedSignal();
		//void CtrlW_PressedSignal();
		//void CtrlX_PressedSignal();
		//void CtrlY_PressedSignal();
		//void CtrlZ_PressedSignal();
	protected slots:
		//void CtrlA_PressedSlot();
		void CtrlB_PressedSlot();
		//void CtrlC_PressedSlot();
		//void CtrlD_PressedSlot();
		//void CtrlE_PressedSlot();
		void CtrlF_PressedSlot();
		//void CtrlG_PressedSlot();
		//void CtrlH_PressedSlot();
		//void CtrlI_PressedSlot();
		//void CtrlJ_PressedSlot();
		//void CtrlK_PressedSlot();
		//void CtrlL_PressedSlot();
		//void CtrlM_PressedSlot();
		void CtrlN_PressedSlot();
		//void CtrlO_PressedSlot();
		void CtrlP_PressedSlot();
		void CtrlQ_PressedSlot();
		//void CtrlR_PressedSlot();
		//void CtrlS_PressedSlot();
		//void CtrlT_PressedSlot();
		//void CtrlU_PressedSlot();
		//void CtrlV_PressedSlot();
		//void CtrlW_PressedSlot();
		//void CtrlX_PressedSlot();
		//void CtrlY_PressedSlot();
		//void CtrlZ_PressedSlot();
};

class SoTextEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	SoTextEdit();
	void keyPressEvent(QKeyEvent *input);
	QTextCharFormat setColor(QColor color);
	QStringList tokenizer(QString text);
	void dump_token(QStringList token);
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();
protected:
	void resizeEvent(QResizeEvent *event);
private:
	int block_stack;
	int tab_width;
	QWidget *lineNumberArea;
	int lineNumberWidth;
signals:
	void returnPressed();
private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void updateLineNumberArea(const QRect &, int);
};

class LineNumberArea : public QWidget
{
	public:
		LineNumberArea(SoTextEdit *editor) : QWidget(editor) {
			codeEditor = editor;
		}

		QSize sizeHint() const {
			return QSize(codeEditor->lineNumberAreaWidth(), 0);
		}

	protected:
		void paintEvent(QPaintEvent *event) {
			codeEditor->lineNumberAreaPaintEvent(event);
		}

	private:
		SoTextEdit *codeEditor;
};
