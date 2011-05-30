#ifndef SOEKeyBind_H$$
#define SOEKeyBind_H$$
#include <QtGui>

class QAction;

class SOEKeyBind :public QAction
{
	Q_OBJECT

	public:
		SOEKeyBind(QObject *parent = 0);
		//void setSOE_MainWidgetKeyBind(QWidget *widget);
		void setSOE_TextKeyBind(QTextEdit *text);
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

#endif
