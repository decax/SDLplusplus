#include "Scrollbar.h"

using namespace SDL;
using namespace std;

Scrollbar::Scrollbar()
{
	SetSize(Size(10, 100));
	
	contentSize = GetSize();
	
	SetHandleSize(0.8f);
	value = 0.0f;
}

void Scrollbar::SetHandleSize(float p_size)
{
	handleSize = p_size;
}

float Scrollbar::GetValue() const
{
	return value;
}

void Scrollbar::DrawForeground()
{
	Control::DrawForeground();
	
	renderer->SetDrawColor(Color::Green);
	renderer->FillRect(Rect(GetPosition(), Size(GetSize().Width, GetSize().Height * handleSize)));
}