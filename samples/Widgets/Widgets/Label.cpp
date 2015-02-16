#include "Label.h"

using namespace SDL;
using namespace std;

Label::Label()
{
	alignment = Alignment::LEFT;
	textSize = Size(0, 0);
}

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
	
	if (autoSize) {
		SetSize(textSize);
	}
}

void Label::DrawForeground()
{
	Control::DrawForeground();
	
	int xOffset;
	switch (alignment) {
		case Alignment::LEFT:   xOffset = 0; break;
		case Alignment::CENTER: xOffset = (GetSize().Width - textSize.Width) / 2; break;
		case Alignment::RIGHT:  xOffset = GetSize().Width - textSize.Width; break;
	}
	
	font.RenderTextBlended(*renderer, text, GetPosition() + Size(xOffset, 0), color);
}

void Label::UpdateTextSize()
{
	textSize = font.GetSize(text);
}