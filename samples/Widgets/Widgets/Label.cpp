#include "Label.h"

using namespace SDL;
using namespace std;

Label::Label()
{
	SetFont("/Library/Fonts/Arial.ttf");
}

void Label::SetFont(const string &p_filename)
{
	// TODO: close opened font
	font.Open(p_filename, 20);
}

void Label::SetText(const string &p_text)
{
	text = p_text;
}

void Label::Draw()
{
	font.RenderTextBlended(*renderer, text, GetPosition());
}

