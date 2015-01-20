#include "Label.h"

using namespace SDL;
using namespace std;

Label::Label()
{
	position = Point(0, 0);
}

void Label::SetPosition(const Point &p_position)
{
	position = p_position;
}

void Label::SetFont(const string &p_filename)
{
	font.Open(p_filename, 20);
}

void Label::SetText(const string &p_text)
{
	text = p_text;
}

void Label::Draw()
{
	font.RenderTextBlended(*renderer, text, position);
}

