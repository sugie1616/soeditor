#include "soeditor.hpp"

void SoToken::setWord(QString text)
{
	word = text;
	return;
}

QString SoToken::getWord(void)
{
	return word;
}

void SoToken::setType(int i)
{
	type = i;
	return;
}

int SoToken::getType(void)
{
	return type;
}
