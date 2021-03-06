#include "Control.h"

#include <SDLplusplus/SDLplusplus.h>

using namespace SDL;
using namespace std;

Control::Control()
{
	renderer = nullptr;
	autoSize = true;

	SetPosition(Point(0, 0));
	SetSize(Size(100, 20));
	
	backgroundColor = Color::Transparent;
	color = Color::White;
}

void Control::SetRenderer(SDL::Renderer &p_renderer)
{
	renderer = &p_renderer;
	
	CreateTextures();
}

void Control::Draw()
{
	DrawBackground();
	DrawForeground();
}

void Control::DrawBackground()
{
	if (backgroundColor != Color::Transparent) {
		renderer->SetDrawColor(backgroundColor);
		renderer->FillRect(rect);
	}
}

void Control::DrawForeground()
{
	renderer->SetDrawColor(color);
}