#include "Button.h"

#include <iostream>

using namespace SDL;
using namespace std;

Button::Button()
{
	SetSize(Size(150, 20));

	state = State::NORMAL;

	clickedCallback = nullptr;
}

void Button::SetRenderer(SDL::Renderer &p_renderer)
{
	Control::SetRenderer(p_renderer);
	
	label.SetRenderer(p_renderer);
}

void Button::CreateTextures()
{
	for (int i = 0; i < 4; i++) {
		textures[i] = Texture(*renderer, PixelFormat::ARGB_8888, Texture::Access::TARGET, rect.Size);
	}
	
	auto oldTarget = renderer->GetRenderTarget();
	
	auto color = Color::Gray;
	
	color = Color::Gray.Darken(0.20f);

	renderer->SetRenderTarget(textures[State::NORMAL]);
	renderer->SetDrawColor(color);
	renderer->FillRect(rect.Size);

	color = Color::Gray.Darken(0.10f);
	
	renderer->SetRenderTarget(textures[State::PRESSED]);
	renderer->SetDrawColor(color);
	renderer->FillRect(rect.Size);

	color = Color::Gray;
	
	renderer->SetRenderTarget(textures[State::HOVERED]);
	renderer->SetDrawColor(color);
	renderer->FillRect(rect.Size);
	
	color = Color::Gray.Darken(0.30);

	renderer->SetRenderTarget(textures[State::DEACTIVATED]);
	renderer->SetDrawColor(color);
	renderer->FillRect(rect.Size);

	renderer->SetRenderTarget(oldTarget);
	
	label.Control::CreateTextures();
}

void Button::SetPosition(const Point &p_position)
{
	Control::SetPosition(p_position);
	
	UpdateLabelPosition();
}

void Button::UpdateLabelPosition()
{
	auto newPos = Point((rect.Size.Width - label.textSize.Width) / 2, (rect.Size.Height - label.textSize.Height) / 2);
	
	label.SetPosition(GetPosition() + newPos);
}

void Button::SetFont(const std::string &p_filename)
{
	label.SetFont(p_filename);
}

void Button::SetText(const std::string &p_text)
{
	label.SetText(p_text);

	UpdateLabelPosition();
}

void Button::DrawBackground()
{
	Control::DrawBackground();

	renderer->Copy(textures[state], GetPosition());
}

void Button::DrawForeground()
{
	Control::DrawForeground();
	
	label.Draw();
}

void Button::Hover(bool p_hovered)
{
	state = p_hovered ? State::HOVERED : State::NORMAL;
}

void Button::Press()
{
	state = State::PRESSED;
}

void Button::Release(bool p_clicked)
{
	state = State::NORMAL;

	if (p_clicked) {
		Click();
	}
}

void Button::Click()
{
	if (clickedCallback) {
		clickedCallback();
	}
}

void Button::RegisterOnClick(std::function<void()> p_onClick)
{
	clickedCallback = p_onClick;
}
