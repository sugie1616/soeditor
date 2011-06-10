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
class SOEMenuAreaWidget;
class SOESubTextAreaWidget;

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
	int settingMenu;
	int fontsize;
	QString fontname;
	int k_Mode;
	std::map<QWidget*, SoTextEdit*> m_textedit_map;
	std::map<QWidget*, QString> m_filename_map;
	QHBoxLayout *m_StatusLayout;
	QHBoxLayout *m_TextLayout;
	QVBoxLayout *m_WholeLayout;
	QHBoxLayout *m_WholeLayout2;

	QLabel *m_FileLabel;
	QLineEdit *m_FileName;
	QPushButton *m_SaveButton;
	QPushButton *m_LoadButton;
	QPushButton *m_SettingButton;

	QTabWidget *m_Tab;
	QToolButton *m_AddTab;
	QToolButton *m_AllowTab;

	QWidget *fileMenuWidget;
	QWidget *mainTextWidget;
	QWidget *subTextWidget;

	SoTextEdit *m_Text;

	QAction *m_AddTabAction;
	QAction *CtrlK;

	QProcess *k_proc;

	SOEKeyBind *keyBind;
	SOEMenuAreaWidget *menuAreaWidget;
	SOESubTextAreaWidget *subTextAreaWidget;

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
	void filemenuViewer(int i);
	void subtextViewer(int i);
	void appendKnhScriptSlot();
};

class SOEMenuAreaWidget : public QWidget
{
	Q_OBJECT

	public :
		SOEMenuAreaWidget();
		void makeMenuAreaWidget();
	private :
		int charSize;
		QString charFont;
		int fileMenuState;
		int subTextState;
		QGroupBox *settingCharGroup;
		QLabel *settingCharSizeLabel;
		QSpinBox *settingCharSizeSpinBox;
		QLabel *settingFontLabel;
		QComboBox *settingFontBox;
		QGroupBox *settingBGGroup;
		QGroupBox *settingDisplayGroup;

		QVBoxLayout *settingMenuLayout;
		private slots :
			void setCharSize(int cs);
		void setCharFont(QString cf);
		void setFileMenuView(int state);
		void setSubTextView(int state);
signals :
		void charSizeChanged(int cs);
		void charFontChanged(QString cf);
		void fileMenuViewChanged(int state);
		void subTextViewChanged(int state);
};

class SOESubTextAreaWidget : public QWidget
{
	Q_OBJECT

	public:
	SOESubTextAreaWidget();
	void makeSubTextAreaWidget();
	private slots:
	void cmdExecSlot();
	void appendViewSlot();
	private:
	QLabel *cmdLabel;
	QLineEdit *cmdLine;
	
	QHBoxLayout *cmdLayout;
	QVBoxLayout *subTextAreaLayout;

	QProcess *proc;

	SoTextEdit *subText;
};

class SOEKeyBind : public QAction
{
	Q_OBJECT

	public:
	SOEKeyBind(QObject *parent = 0);
	void setSOE_TextKeyBind(SoTextEdit *text);
	void setSOE_WindowKeyBind(QMainWindow *window);
signals:
	void CtrlB_PressedSignal();
	void CtrlF_PressedSignal();
	void CtrlN_PressedSignal();
	void CtrlP_PressedSignal();
	void CtrlQ_PressedSignal();
	protected slots:
		void CtrlB_PressedSlot();
	void CtrlF_PressedSlot();
	void CtrlN_PressedSlot();
	void CtrlP_PressedSlot();
	void CtrlQ_PressedSlot();
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
