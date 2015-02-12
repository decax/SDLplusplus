#include "Label.h"

using namespace SDL;
using namespace std;

void Label::CreateTextures()
{
	// TODO: optimization
}

void Label::SetFont(const string &p_filename)
{
	font.Open(p_filename, 20);
}

void Label::SetText(const string &p_text)
{
	text = p_text;

	UpdateTextSize();
}

void Label::DrawForeground()
{
	Control::DrawForeground();
	
	font.RenderTextBlended(*renderer, text, GetPosition(), color);
}

void Label::UpdateTextSize()
{
	textSize = font.GetSize(text);
}