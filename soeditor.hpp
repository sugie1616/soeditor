#include <konoha1.h>
#include <QtGui>
#include <iostream>
#include <list>
#include <map>


#define LINE_SIZE 256
#define OFF 0
#define ON 1
#define UNVALID_BLOCK (-1)
#define MAX_TOKEN_SIZE 256

class SoTextEdit;
class Widget;
class SOEKeyBind;
class SoToken;

class MainWindow : public QMainWindow
{
	Q_OBJECT;
private:
	QMenu *m_FileMenu;
	QMenu *m_ViewMenu;
	int countBG;
	int lineNum;
	int cursorcolumn;
	int cursorline;

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

	void createMenus();
	void createTimeStatusBar();
public:
	MainWindow(QWidget * iParent = 0, Qt::WindowFlags iFlags = 0);
protected slots:
	void setCurrentTime();
	void setWindowBG();
	void createTextCursorPositionStatusBar();
	void setCurrentTabStatus(int t);//
};

class Widget : public QWidget
{
	Q_OBJECT;
private:
	int countTab;
	int tabRemoveChecker;
	QString fontname;
	int fontsize;
	int settingMenu;
	int k_Mode;
	std::map<QWidget*, SoTextEdit*> m_textedit_map;
	std::map<QWidget*, QString> m_filename_map;
	QHBoxLayout *m_StatusLayout;
	QHBoxLayout *m_CmdLayout;
	QHBoxLayout *m_TextLayout;
	QVBoxLayout *m_SubTextLayout;
	QVBoxLayout *m_WholeLayout;
	QVBoxLayout *m_SettingMenuLayout;
	QHBoxLayout *m_WholeLayout2;

	QLabel *m_FileLabel;
	QLineEdit *m_FileName;
	QPushButton *m_SaveButton;
	QPushButton *m_LoadButton;
	QPushButton *m_SettingButton;
		
	QGroupBox *m_SettingCharGroup;
	QLabel *settingCharSizeLabel;
	QSpinBox *settingCharSizeSpinBox;
	QLabel *settingFontLabel;
	QComboBox *settingFontBox;
	QGroupBox *m_SettingBGGroup;
	QGroupBox *m_SettingDisplayGroup;

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
public:
	Widget(QWidget * iParent = 0, Qt::WindowFlags iFlags = 0);
	void makeWidgets();
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
	int filenameChange(int i);
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
	void appendKnhScriptSlot();
	void filemenuViewer(int i);
	void subtextViewer(int i);
};

class SOEKeyBind :public QAction
{
	Q_OBJECT;

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
	Q_OBJECT;

private:
	int block_stack;
	int tab_width;
	QWidget *lineNumberArea;
	int lineNumberWidth;

	QStringList *exception;
	QStringList *type;
	QStringList *keyword;

	QColor *builtin_color;
	QColor *comment_color;
	QColor *stirng_color;
	QColor *keyword_color;
	QColor *constant_color;
	QColor *function_color;
	QColor *variable_color;
	QColor *type_color;
	QColor *warning_color;
	QColor *default_color;

public:
	typedef enum {
		t_TYPE,
		t_KEYWORD,
		t_DEFAULT,
		t_COMMENT,
		t_STRING,
		t_SPACE
	} tokenType;

	SoTextEdit();
	void keyPressEvent(QKeyEvent *input);
	QTextCharFormat colorFormat(QColor *color);
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();
	void initializePatternList();
	int checkType(QString text);
	int autoIndent(QTextCursor cursor);
	int indentCount(QString text);
	int findBraceLeft(void);
	SoToken** tokenizer(QString text);
	void dumpToken(SoToken **token_list);
protected:
	void resizeEvent(QResizeEvent *event);
signals:
	void returnPressed();
private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void updateLineNumberArea(const QRect &, int);
};

class LineNumberArea : public QWidget
{
private:
	SoTextEdit *codeEditor;

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

};

class SoToken
{
private:
	QString word;
	int type;
public:
	void setWord(QString text);
	QString getWord(void);
	void setType(int i);
	int getType(void);
};
