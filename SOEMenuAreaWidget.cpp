#include "soeditor.hpp"
SOEMenuAreaWidget::SOEMenuAreaWidget() : QWidget(){
	charSize = 12;
	charFont = "monospace";
	fileMenuState = Qt::Checked;
	subTextState = Qt::Checked;
	makeMenuAreaWidget();

}
void SOEMenuAreaWidget::makeMenuAreaWidget()
{
//Make Setting Menu Area
settingCharGroup = new QGroupBox("Set Char");
QVBoxLayout *settingCharGroupLayout = new QVBoxLayout;
settingCharSizeLabel = new QLabel(tr("Size:"));
settingCharSizeSpinBox = new QSpinBox();
settingCharSizeSpinBox->setRange(12, 64);
connect(settingCharSizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setCharSize(int)));

QHBoxLayout *settingCharSizeLayout = new QHBoxLayout();
settingCharSizeLayout->addWidget(settingCharSizeLabel);
settingCharSizeLayout->addWidget(settingCharSizeSpinBox);
settingFontLabel = new QLabel(tr("Font:"));
settingFontBox = new QComboBox();
settingFontBox->addItem("Arial");
settingFontBox->addItem("Impact");
settingFontBox->addItem("Serif");
settingFontBox->addItem("Monospace");
connect(settingFontBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setCharFont(QString)));

QHBoxLayout *settingFontLayout = new QHBoxLayout();
settingFontLayout->addWidget(settingFontLabel);
settingFontLayout->addWidget(settingFontBox);
settingCharGroupLayout->addLayout(settingCharSizeLayout);
settingCharGroupLayout->addLayout(settingFontLayout);
settingCharGroup->setLayout(settingCharGroupLayout);

settingBGGroup = new QGroupBox("Set Background");

settingDisplayGroup = new QGroupBox("Set Display Area");
QCheckBox *fileMenuViewBox  = new QCheckBox("File Menu Area");
connect(fileMenuViewBox, SIGNAL(stateChanged(int)), this, SLOT(setFileMenuView(int)));
QCheckBox *subTextViewBox  = new QCheckBox("Sub Text Area");
connect(subTextViewBox, SIGNAL(stateChanged(int)), this, SLOT(setSubTextView(int)));
QVBoxLayout *areaBoxLayout = new QVBoxLayout;
fileMenuViewBox->setChecked (true);
subTextViewBox->setChecked (true);
areaBoxLayout->addWidget(fileMenuViewBox);
areaBoxLayout->addWidget(subTextViewBox);
settingDisplayGroup->setLayout(areaBoxLayout);
settingMenuLayout = new QVBoxLayout();
settingMenuLayout->addWidget(settingCharGroup);
settingMenuLayout->addWidget(settingBGGroup);
settingMenuLayout->addWidget(settingDisplayGroup);
setLayout(settingMenuLayout);

QPalette basicalWidgetPalette;
basicalWidgetPalette.setColor(QPalette::Background, Qt::white);
setPalette(basicalWidgetPalette);
setAutoFillBackground(true);

//
}
void SOEMenuAreaWidget::setCharSize(int cs){
	charSize = cs;
			emit	charSizeChanged(charSize);
}
void SOEMenuAreaWidget::setCharFont(QString cf){
			charFont = cf;
			emit	charFontChanged(charFont);
}
void SOEMenuAreaWidget::setFileMenuView(int state){
			fileMenuState = state;
			emit	fileMenuViewChanged(state);
}
void SOEMenuAreaWidget::setSubTextView(int state){
				subTextState = state;
				emit subTextViewChanged(subTextState);
}
