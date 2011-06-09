#include "soeditor.hpp"

using namespace std;

SoTextEdit::SoTextEdit() 
{
	block_stack = 0;
	setPlainText(tr(""));
	setCursorWidth(6);
	ensureCursorVisible();

	setTabStopWidth(20);

	type_color = new QColor(Qt::darkGreen);
	keyword_color = new QColor(Qt::darkMagenta);
	default_color = new QColor(Qt::black);

	exception = new QStringList;
	type = new QStringList;
	keyword = new QStringList;

	initializePatternList();

	lineNumberArea = new LineNumberArea(this);
	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(const QRect &, int)), this, SLOT(updateLineNumberArea(const QRect &, int)));
	updateLineNumberAreaWidth(0);
}


void SoTextEdit::initializePatternList()
{
	const char *e[] = {" ", ";", "(", ")", NULL};
	for (int count = 0; e[count] != NULL; count++ ) {
		(*exception) << e[count];
	}

	const char *t[] = {
		"void", "char", "short", "int", "long", "float",
		"double", "auto", "static", "const", "signed",
		"unsigned", "extern", "volatile", "register", NULL
	};
	for (int count = 0; t[count] != NULL; count++) {
		*type << t[count];
	}

	const char *k[] = {
//for c
		"return", "goto", "if", "else", "switch",
		"case", "default", "break", "for",
		"while", "do", "continue", "typedef",
		"struct", "enum", "union", "sizeof",
//for c++
		"private", "protected", "class", "public", NULL
	};
	for (int count = 0; k[count] != NULL; count++) {
		*keyword << k[count];
	}
}

void SoTextEdit::keyPressEvent(QKeyEvent *input)
{
	QTextCursor cursor = textCursor();
	QString text;
	QStringList list;
	QTextBlock block;
	int position = 0;
//	int position_in_block = 0;
	int count;

	if (input->modifiers() != Qt::NoModifier &&
		input->modifiers() != Qt::ShiftModifier) {
		input->ignore();
		return;
	}

	switch (input->key()) {
	case Qt::Key_Shift:
	case Qt::Key_Control:
	case Qt::Key_unknown:
		input->ignore();
		return;
	case Qt::Key_BraceLeft:
		cursor.insertText(input->text(), colorFormat(default_color));
		std::cout << block_stack << std::endl;
		return;
	case Qt::Key_BraceRight:
		cursor.insertText("}");
		position = autoIndent(cursor);
		cursor.setPosition(position);
		setTextCursor(cursor);
		return;
	case Qt::Key_Return:
		emit returnPressed();

		position = cursor.position();

		cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
		text = cursor.selectedText();
		for (count = 0; count <= text.size(); count++) {
			if (text[count] == QChar('{')) {
				block_stack++;
			} else if (text[count] == QChar('}')) {
				block_stack--;
			}
		}


		cursor.setPosition(position);

		if (cursor.atBlockEnd()) {
			cursor.insertText(input->text());
			position++;
		} else {
			cursor.setPosition(position + 1, QTextCursor::MoveAnchor);
			cursor.setPosition(position - 1, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
			for (count = 0; count < exception->count(); count++) {
				if (text[0] == (*exception)[count][0] ||
					text[1] == (*exception)[count][0]) {
					cursor.setPosition(position);
					cursor.insertText(input->text());
					position = autoIndent(cursor);
					cursor.setPosition(position);
					setTextCursor(cursor);
					return;
				}
			}

			cursor.setPosition(position, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
			switch (checkType(text)) {
			case t_TYPE:
				cursor.insertText(text, colorFormat(type_color));
				break;
			case t_KEYWORD:
				cursor.insertText(text, colorFormat(keyword_color));
				break;
			case t_DEFAULT:
				cursor.insertText(text, colorFormat(default_color));
			}

			cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
			switch (checkType(text)) {
			case t_TYPE:
				cursor.insertText(text, colorFormat(type_color));
				break;
			case t_KEYWORD:
				cursor.insertText(text, colorFormat(keyword_color));
				break;
			case t_DEFAULT:
				cursor.insertText(text, colorFormat(default_color));
			}

			cursor.setPosition(position);
			cursor.insertText(input->text());
			position++;
		}

		position = autoIndent(cursor);
		cursor.setPosition(position);
		setTextCursor(cursor);
		return;

	case Qt::Key_Tab:
		cout << "tab" << endl;
		position = autoIndent(cursor);
		cursor.setPosition(position);
		setTextCursor(cursor);
		std::cout << "block_stack" << block_stack << std::endl;
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
	case Qt::Key_Space:
		if (cursor.atBlockEnd()) {
			cursor.insertText(input->text());
			setTextCursor(cursor);
			return;
		} else {
			position = cursor.position();
			cursor.setPosition(position - 1, QTextCursor::MoveAnchor);
			cursor.setPosition(position + 1, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			for (count = 0; count < exception->count(); count++) {
				if (text[0] == (*exception)[count][0] ||
					text[1] == (*exception)[count][0]) {
					cursor.setPosition(position);
					cursor.insertText(input->text());
					setTextCursor(cursor);
					return;
				}
			}
			
			cursor.setPosition(position, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
			switch (checkType(text)) {
			case t_TYPE:
				cursor.insertText(text, colorFormat(type_color));
				break;
			case t_KEYWORD:
				cursor.insertText(text, colorFormat(keyword_color));
				break;
			case t_DEFAULT:
				cursor.insertText(text, colorFormat(default_color));
			}

			cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
			switch (checkType(text)) {
			case t_TYPE:
				cursor.insertText(text, colorFormat(type_color));
				break;
			case t_KEYWORD:
				cursor.insertText(text, colorFormat(keyword_color));
				break;
			case t_DEFAULT:
				cursor.insertText(text, colorFormat(default_color));
			}

			cursor.setPosition(position);
			cursor.insertText(input->text());
			setTextCursor(cursor);
			return;
		}
	case Qt::Key_Delete:
		position = cursor.position();
		cursor.deleteChar();

		cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
		text = cursor.selectedText();
		cursor.setPosition(position);
		for (count = 0; count < exception->count(); count++) {
			if (text[0] == (*exception)[count][0]) {
				cursor.setPosition(position - 1);
			}
		}

		cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
		text = cursor.selectedText();
		break;
	case Qt::Key_Backspace:
		if (cursor.atStart()) {
			return;
		} else if (cursor.atBlockStart()) {
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

			cursor.setPosition(position, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
			text = cursor.selectedText();
		} else {
			position = cursor.position() - 1;
			cursor.deletePreviousChar();
			cursor.movePosition(QTextCursor::NoMove, QTextCursor::MoveAnchor);
			cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
			text = cursor.selectedText();

			for (count = 0; count < exception->count(); count++) {
				if (text[0] == (*exception)[count][0]) {
					cursor.setPosition(position - 1);
					cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
					cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
					text = cursor.selectedText();
					break;
				}
			}

			if (count == exception->count()) {
				cursor.setPosition(position);
				cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
				cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
				text = cursor.selectedText();
			}
		}

		std::cout << block_stack <<std::endl;
		break;
	default:
		position = cursor.position() + 1;
		cursor.insertText(input->text());
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::MoveAnchor);
		cursor.movePosition(QTextCursor::EndOfWord, QTextCursor::KeepAnchor);
		text = cursor.selectedText();
	}

	qDebug() << text;

	if (text.isEmpty()) {
		return;
	}

	switch (checkType(text)) {
	case t_TYPE:
		cursor.insertText(text, colorFormat(type_color));
		break;
	case t_KEYWORD:
		cursor.insertText(text, colorFormat(keyword_color));
		break;
	case t_DEFAULT:
		cursor.insertText(text, colorFormat(default_color));
	}

	cursor.setPosition(position);
	setTextCursor(cursor);
	return;
}

int SoTextEdit::autoIndent(QTextCursor cursor)
{
	QString text, tab_part;
	int position = cursor.position();

	cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
	cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
	text = cursor.selectedText();

	int	count = indentCount(text);

	if (count == text.size()) {
		tab_part.fill('\t', block_stack);
		cursor.insertText(tab_part);
		position = cursor.position();
		return position;
	} else {
		text = text.mid(count);

		if (0 <= block_stack) {
			if (text.contains(QChar('}'), Qt::CaseSensitive)) {
				int rb_count = 0;
				QTextCursor lb_locate = textCursor();
				while (text[rb_count] == QChar('}')) {
					rb_count++;
				}
				lb_locate.setPosition(findBraceLeft());
				cout << "position" << findBraceLeft() << endl;
				lb_locate.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
				cout << "position" << lb_locate.position() << endl;
				lb_locate.movePosition(QTextCursor::StartOfLine,QTextCursor::KeepAnchor);
				cout << "position" << lb_locate.position() << endl;

				cout << "block text  \"" << qPrintable(lb_locate.selectedText()) <<"\""<< endl;

				int indent_count = indentCount(lb_locate.selectedText());

				tab_part.fill('\t', indent_count);
				position = position - count + (indent_count);
			} else {
				tab_part.fill('\t', block_stack);
				position = position - count + (tab_width * block_stack);
			}
			text.prepend(tab_part);
			cout << qPrintable(text) << endl; 
			cursor.insertText(text, colorFormat(default_color));
		} else {
			position = position - count;
			cursor.insertText("");
		}
		return position;
	}
}

int SoTextEdit::checkType(QString text)
{
	for (int count = 0; count < type->count(); count++) {
		if (text == (*type)[count]) {
			return t_TYPE;
		}
	}
	for (int count = 0; count < keyword->count(); count++) {
		if (text == (*keyword)[count]) {
			return t_KEYWORD;
		}
	}
	return t_DEFAULT;
}

QTextCharFormat SoTextEdit::colorFormat(QColor *color)
{
	QBrush b = QBrush(*color, Qt::SolidPattern);
	QTextCharFormat f;
	f.setForeground(b);
	return f;
}

int SoTextEdit::findBraceLeft(void)
{
	QTextCursor cursor = textCursor();
 	QTextBlock block = cursor.block();
	int brace_count = 0, i, blockNumber = block.blockNumber();
	QString text;

	while (blockNumber != UNVALID_BLOCK) {
		text = block.text();
		i = text.size();
		for (; 0 <= i; i--) {
			if (text[i] == QChar('}')) {
				brace_count++;
			} else if (text[i] == QChar('{')) {
				brace_count--;
				if (brace_count == 0) {
					// cursor.deletePreviousChar();
					// cursor.insertText("}", colorFormat(Qt::darkCyan));

					 cursor.setPosition((block.position()) + i);
					// cursor.deleteChar();
					// cursor.insertText("{", colorFormat(Qt::darkCyan));

					 return (block.position() + i);
				}
			}
		}
		block = block.previous();
		blockNumber = block.blockNumber();
	}
	return -1;
}

int SoTextEdit::indentCount(QString text)
{
	int count = 0;
	while (text[count] == QChar('\t')) {
		count++;
	}
	return count;
}

// SoToken** SoTextEdit::tokenizer(QString text)
// {
// 	SoToken **token_list = (SoToken**)malloc(sizeof(SoToken*) * MAX_TOKEN_SIZE);
// 	int token_count = 0;
// 	for(int text_count = 0; text.isNull(); ) {
// 		if (text[text_count] == QChar('"')) {
// 			do {
// 				text_count++;
// 			} while(text[text_count] != QChar('"') ||
// 					text[text_count] != QChar('\0'));
// 			SoToken *temp = (SoToken*)malloc(sizeof(SoToken));
// 			text_count++;
// 			temp->setWord(text.left(text_count));
// 			temp->setType(t_STRING);
// 			token_list[token_count] = temp;
// 			token_count++;

// 			text = text.mid(text_count);
// 			text_count = 0;

// 			qDebug() << temp->getWord();
// 		} else if (text[text_count] == QChar(' ')) {
// 			do {
// 				text_count++;
// 			} while(text[text_count] == QChar(' '));
// 			SoToken *temp = (SoToken*)malloc(sizeof(SoToken));
// 			temp->setWord(text.left(text_count));
// 			temp->setType(t_SPACE);
// 			token_list[token_count] = temp;
// 			token_count++;

// 			text = text.mid(text_count);
// 			text_count = 0;
// 			qDebug() << temp->getWord();
// 		} else if (text[text_count].isLetterOrNumber()) {
// 			do {
// 				text_count++;
// 			} while(text[text_count].isLetterOrNumber());
// 			SoToken *temp = (SoToken*)malloc(sizeof(SoToken));
// 			temp->setWord(text.left(text_count));
// 			temp->setType(checkType(temp->getWord()));
// 			token_list[token_count] = temp;
// 			token_count++;

// 			text = text.mid(text_count);
// 			text_count = 0;
// 			qDebug() << temp->getWord();
// 		} else {
// 			SoToken *temp = (SoToken*)malloc(sizeof(SoToken));
// 			temp->setWord(text.left(1));
// 			temp->setType(t_DEFAULT);
// 			token_list[token_count] = temp;
// 			token_count++;

// 			text = text.mid(1);
// 			text_count = 0;
// 			qDebug() << temp->getWord();
// 		}






// 	}
// 	token_list[token_count] = NULL;
// 	return token_list;
// }

// void SoTextEdit::dumpToken(SoToken **token_list)
// {
// 	int token_count = 0;
// 	while (token_list[token_count] == NULL) {
// 		qDebug() << token_list[token_count]->getWord();
// 		cout << token_list[token_count]->getType() << endl;
// 		token_count++;
// 	}
// }



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
