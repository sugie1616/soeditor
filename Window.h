#ifndef CustomMainWindow_H
#define CustomMainWindow_H
#include "Widget.h"
#include <QMainWindow>
#include <QtGui>

class QAction;
class QListWidget;
class QMenu;
class Widget;
class QPalette;
class QDateTime;
class QTimer;
class QImage;
class SOEKeyBind;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	public:
		MainWindow(QWidget * iParent = 0, Qt::WindowFlags iFlags = 0);
	protected slots:
		void setCurrentTime(); 
		void setWindowBG();
		void createTextCursorPositionStatusBar();
	private:
		void createMenus();
		QMenu *m_FileMenu;
		QMenu *m_ViewMenu;
		int countBG;
		int cursorcolumn;
		int cursorline;

		void createTimeStatusBar();
		QPalette *plt;

		QDateTime dt;
		QString now;
		QLabel *timeLabel;
		QLabel *cursorPositionLabel;

		Widget *m_Widget;

		SOEKeyBind *keyBind;

		QPalette palette;
		QImage w_bgImage;
};
#endif 

