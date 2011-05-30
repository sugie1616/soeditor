#ifndef STE_H
#define STE_H
#include <QtGui>
#include <QStringList>
#include <vector>
#include <iostream>
#include <string>

#define ASCII_START 32
#define ASCII_END 127



class SoTextEdit : public QTextEdit
{
  Q_OBJECT


private:

public:
  SoTextEdit();
  void keyPressEvent(QKeyEvent *input);
  QTextCharFormat setColor(QColor color);
  QStringList tokenizer(QString text);
  void dump_token(QStringList token);

};

#endif
