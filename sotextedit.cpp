#include "soeditor.h"

using namespace std;

SoTextEdit::SoTextEdit() 
{
	block_stack = 0;
	tab_width = 4;
	setPlainText(tr(""));
	setCursorWidth(6);
	ensureCursorVisible();

	lineNumberArea = new LineNumberArea(this);
	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
	updateLineNumberAreaWidth(0);
}

void SoTextEdit::keyPressEvent(QKeyEvent *input)
{

	QTextCursor cursor = textCursor();
	QString text;
	QTextBlock block;
	int position = 0;
	//int position_in_block = 0;
	int count;

	switch (input->key()) {
	case Qt::Key_Shift:
	case Qt::Key_Control:
	case Qt::Key_unknown:
		input->ignore();
		return;
	case Qt::Key_BraceLeft:
		cursor.insertText(input->text());
		std::cout << block_stack << std::endl;
		return;
	case Qt::Key_BraceRight:
		position = cursor.position();
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		text = cursor.selectedText();

		count = 0;
		while (text[count] == QChar(' ')) {
			count++;
		}
		text = text.mid(count);
		cursor.insertText(text);

		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);

		if (0 < block_stack) {
			text.fill(' ', tab_width * (block_stack - 1));
			cursor.insertText(text);
			position = position - count + (tab_width * (block_stack - 1));
			cursor.setPosition(position);
			cursor.insertText(input->text());
			setTextCursor(cursor);
		} else {
			cursor.insertText("");
			position = position - count;
			cursor.setPosition(position);
			cursor.insertText(input->text());
			setTextCursor(cursor);
		}

		std::cout << block_stack << std::endl;
		return;

	case Qt::Key_Return:
		cursor.insertText(input->text());
		cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		text = cursor.selectedText();
		count = 0;
		while (count <= text.size()) {
			if (text[count] == QChar('{')) {
				block_stack++;
			} else if (text[count] == QChar('}')) {
				block_stack--;
			}
			count++;
		}
		if (0 < block_stack) {
			cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
			cursor.insertText(text.fill(' ', tab_width * block_stack));
		}
		std::cout << block_stack << std::endl;
		emit returnPressed();
		return;
		cursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor);
		std::cout << block_stack << std::endl;

		emit returnPressed();

	case Qt::Key_Tab:
		position = cursor.position();
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
		text = cursor.selectedText();

		count = 0;
		while (text[count] == QChar(' ')) {
			count++;
		}

		if (count == text.size()) {
			text.fill(' ', tab_width * block_stack);
			cursor.insertText(text);
			return;
		}

		text = text.mid(count);
		cursor.insertText(text);
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);

		if (0 < block_stack) {
			if (text.contains(QChar('}'), Qt::CaseSensitive)) {
				text.fill(' ', tab_width * (block_stack - 1));
				position = position - count + (tab_width * (block_stack - 1));
			} else {
				text.fill(' ', tab_width * block_stack);
				position = position - count + (tab_width * block_stack);
			}
			cursor.insertText(text);
			cursor.setPosition(position);
			setTextCursor(cursor);
		} else {
			cursor.insertText("");
			position = position - count;
			cursor.setPosition(position);
			setTextCursor(cursor);
		}
		std::cout << block_stack << std::endl;
		return;
	case Qt::Key_Left:
		if (cursor.atBlockStart()) {
			cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
			position = cursor.position();
			cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			count = 0;
			while (count < text.size()) {
				if (text[count] == QChar('{')) {
					block_stack--;
				} else if (text[count] == QChar('}')) {
					block_stack++;
				}
				count++;
			}
			cursor.setPosition(position, QTextCursor::MoveAnchor);
		} else {
			cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
		}
		setTextCursor(cursor);
		std::cout << block_stack << std::endl;
		return;
	case Qt::Key_Right:
		if (cursor.atEnd()) {
			return;
		} else if (cursor.atBlockEnd()) {
			cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			count = 0;
			while (count < text.size()) {
				if (text[count] == QChar('{')) {
					block_stack++;
				} else if (text[count] == QChar('}')) {
					block_stack--;
				}
				count++;
			}
		}
		cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor);
		setTextCursor(cursor);
		std::cout << block_stack << std::endl;
		return;
	case Qt::Key_Down:
		block = cursor.block();
		if ((block.blockNumber() + 1 ) == blockCount()) {
			return;
		} else {
			position = cursor.position();

			cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			count = 0;
			while (count < text.size()) {
				if (text[count] == QChar('{')) {
					block_stack++;
				} else if (text[count] == QChar('}')) {
					block_stack--;
				}
				count++;
			}

			cursor.setPosition(position);
			cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor);
			setTextCursor(cursor);
			std::cout << block_stack << std::endl;
			return;
		}
	case Qt::Key_Up:
		block = cursor.block();
		if (block.blockNumber() == 0) {
			return;
		} else {
			cursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
			position = cursor.position();

			cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			count = 0;
			while (count < text.size()) {
				if (text[count] == QChar('{')) {
					block_stack--;
				} else if (text[count] == QChar('}')) {
					block_stack++;
				}
				count++;
			}

			cursor.setPosition(position);
			setTextCursor(cursor);
			std::cout << block_stack << std::endl;
			return;
		}
	case Qt::Key_Backspace:
		if (cursor.atBlockStart()) {
			position = cursor.position() - 1;
			cursor.deletePreviousChar();
			cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			std::cout << "debug_text   " << qPrintable(text) << std::endl;

			count = 0;
			while (count < text.size()) {
				if (text[count] == QChar('{')) {
					block_stack--;
				} else if (text[count] == QChar('}')) {
					block_stack++;
				}
				count++;
			}

			cursor.setPosition(position);
			cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
		} else {
			position = cursor.position() - 1;
			cursor.deletePreviousChar();
			cursor.setPosition(position, QTextCursor::MoveAnchor);
		}

		if (cursor.atEnd() ||
			cursor.atBlockEnd()) {
			cursor.setPosition(position - 1, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
		} else {
			cursor.setPosition(position + 1, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
			if (text[0] == QChar(' ')) {
				cursor.setPosition(position - 1, QTextCursor::MoveAnchor);
				cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::MoveAnchor);
				cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
			} else {
				cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::MoveAnchor);
				cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
			}
		}
		text = cursor.selectedText();

		std::cout << block_stack <<std::endl;
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


void SoTextEdit::resizeEvent(QResizeEvent *event)
{
	QPlainTextEdit::resizeEvent(event);
	QRect r = rect();
	lineNumberArea->setGeometry(QRect(r.left(), r.top(), lineNumberAreaWidth(), r.height()));
}

int SoTextEdit::lineNumberAreaWidth()
{
	QTextCursor t_cursor = textCursor();
	int digits = 1;
	int max = qMax(1, t_cursor.blockNumber());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space*2;
}

void SoTextEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void SoTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void SoTextEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QTextCursor t_cursor = textCursor();
	QPainter painter(lineNumberArea);
	painter.fillRect(event->rect(), Qt::white);
	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();
	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
					Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}
