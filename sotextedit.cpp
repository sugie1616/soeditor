#include "sotextedit.h"

using namespace std;

SoTextEdit::SoTextEdit()
{

	setPlainText(tr(""));
	setCursorWidth(6);
	ensureCursorVisible();
	setFont(QFont("Arial",12));

}

void SoTextEdit::keyPressEvent(QKeyEvent *input)
{

	QTextCursor cursor = textCursor();
	QString text;
	int position = 0;
	int position_in_block = 0;

  // std::cout << input->key() << std::endl;
  // std::cout << input->count() << std::endl;
  // std::cout << cursor.position() << std::endl;
  // std::cout << cursor.positionInBlock() << std::endl;

	switch (input->key()) {
	case Qt::Key_Shift:
	case Qt::Key_Control:
	case Qt::Key_unknown:
		//	position = cursor.position();  
		//	break;
		input->ignore();
		return;
	case Qt::Key_Tab:
		cursor.insertText("    ");
		setTextCursor(cursor);
		return;
	case Qt::Key_Left:
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		return;
	case Qt::Key_Right:
		cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		return;
	case Qt::Key_Down:
		cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		return;
	case Qt::Key_Up:
		cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		return;
	case Qt::Key_Backspace:
		position = cursor.position() - 1;
		cursor.deletePreviousChar();
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		text = cursor.selectedText();  	
		break;
	default:
		position = cursor.position() + 1;
		cursor.insertText(input->text());
		cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
		text = cursor.selectedText();
	}
	
	qDebug() << text;

	if (text.isEmpty()) {
		return;
	}

//	QStringList token;
//	token = tokenizer(text);
//	dump_token(token);
	// int token_end = token.count();
	// int count = 0;

	// if (token[0][0] == QChar(' ')) {
	// 	if (token.count() >= 2) {
	// 		count++;
	// 	}
	// }
	// if (token[count][0] == QChar('#')) {
	// 	cursor.insertText(token[count], setColor(Qt::darkRed));
	// 	count++;
	// 	while (count < token_end) {
	// 		cursor.insertText(token[count], setColor(Qt::cyan));
	// 		count++;
	// 	}
	// } else {
	// 	while (count < token_end) {
	if (token[count] == QString("void")) {
		cursor.insertText(token[count], setColor(Qt::darkMagenta));
	// 		} else if (token[count] == QString("char")) {
	// 			cursor.insertText(token[count], setColor(Qt::darkMagenta));
	// 		} else {
	// 			cursor.insertText(token[count],setColor(Qt::black));
	// 		}
	// 		count++;
	// 	}
	// }
	cursor.setPosition(position, QTextCursor::MoveAnchor);
	setTextCursor(cursor);
}

QTextCharFormat SoTextEdit::setColor(QColor color)
{
	QBrush b = QBrush(color, Qt::SolidPattern);
	QTextCharFormat f;
	f.setForeground(b);
	return f;
}

QStringList SoTextEdit::tokenizer(QString text)
{
	QStringList token;
	int end = text.length();
	int end_count = 0;
	int str_count = 0;

	if (!(text[0] == QChar(' '))) {
		goto if_else;
	}
  
if_space:
	while (end_count < end) {
		if (!(text[str_count] == QChar(' '))) {
			token << text.left(str_count);
			text = text.mid(str_count);
			str_count = 0;
			goto if_else;
		}
		end_count++;
		str_count++;
	}

	token << text.left(str_count);
	return token;

if_else:
	while (end_count < end) {
	  if (text[str_count] == QChar(' ')) {
		  token << text.left(str_count);
		  text = text.mid(str_count);
		  str_count = 0;
		  goto if_space;
	  }
	  end_count++;
	  str_count++;
	}
	token << text.left(str_count);
	return token;
}

void SoTextEdit::dump_token(QStringList token)
{
	while (!token.empty()) {
		std::cout << "dump_token    " << "\"" << qPrintable(token.back()) << "\"" << std::endl;
		token.pop_back();
	}
}
