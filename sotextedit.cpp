#include "soeditor.h"

using namespace std;

SoTextEdit::SoTextEdit()
{
	block_stack = 0;
	tab_width = 4;
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
	int count;

	switch (input->key()) {
	case Qt::Key_Shift:
	case Qt::Key_Control:
	case Qt::Key_unknown:
		input->ignore();
		return;
	case Qt::Key_BraceLeft:
		cursor.insertText(input->text());
		block_stack++;
		std::cout << block_stack << std::endl;
		return;
	case Qt::Key_BraceRight:
		cursor.insertText(input->text());
		block_stack--;
		std::cout << block_stack << std::endl;
		return;
//	case Qt::Key_Return:
		// cursor.insertText(input->text());
		// cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);
		// cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		// text = cursor.selectedText();
		// count = 0;
		// while (count < text.size()) {
		// 	if (text[count] == QChar('{')) {
		// 		block_stack++;
		// 	} else if (text[count] == QChar('}')) {
		// 		block_stack--;
		// 	}
		// 	count++;
		// }
		// cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
		// cursor.insertText(text.fill(' ', tab_width * block_stack));
		// return;
	case Qt::Key_Tab:
		position = cursor.position() + (tab_width * block_stack);
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
 		text = cursor.selectedText();

		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		if (text[0] == QChar(' ')) {
			cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor);
		}
 		text.fill(' ', tab_width * block_stack);
 		cursor.insertText(text);
		cursor.setPosition(position);
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
		cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
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

//for c
	if (text == QString("void")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("char")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("short")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("int")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("long")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("float")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("double")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("out")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("static")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("const")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("signed")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("unsigned")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("extern")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("volatile")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("register")) {
		cursor.insertText(text, setColor(Qt::darkGreen));
	} else if (text == QString("return")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("goto")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("if")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("else")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("switch")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("case")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("default")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("break")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("for")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("while")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("do")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("continue")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("typedef")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("struct")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("enum")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("union")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("sizeof")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));

//for c++
	} else if (text == QString("private")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("protected")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("class")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else if (text == QString("public")) {
		cursor.insertText(text, setColor(Qt::darkMagenta));
	} else {
		cursor.insertText(text, setColor(Qt::black));
	}

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
