#include "Button.h"

using namespace SDL;
using namespace std;

Button::Button()
{
	state = State::NORMAL;
	SetSize(Size(150, 20));
}

void Button::SetRenderer(SDL::Renderer &p_renderer)
{
	Control::SetRenderer(p_renderer);
	
	label.SetRenderer(p_renderer);
}

void Button::CreateTextures()
{
	textures[State::NORMAL]  = Texture(*renderer, PixelFormat::ARGB_8888, Texture::Access::TARGET, GetSize());
	textures[State::PRESSED] = Texture(*renderer, PixelFormat::ARGB_8888, Texture::Access::TARGET, GetSize());
	
	auto oldTarget = renderer->GetRenderTarget();

	renderer->SetRenderTarget(textures[State::NORMAL]);
	renderer->SetDrawColor(Color::Gray);
	renderer->FillRect(GetSize());

	renderer->SetRenderTarget(textures[State::PRESSED]);
	renderer->SetDrawColor(Color::Gray.Darken(0.10));
	renderer->FillRect(GetSize());
	
	renderer->SetRenderTarget(oldTarget);
}

void Button::SetPosition(const Point &p_position)
{
	Control::SetPosition(p_position);
	label.SetPosition(p_position);
}

void Button::SetFont(const std::string &p_filename)
{
	label.SetFont(p_filename);
}

void Button::SetText(const std::string &p_text)
{
	label.SetText(p_text);
}

void Button::Draw()
{
	renderer->Copy(textures[state], GetPosition());
	label.Draw();
}

void Button::OnClick(std::function<void()> p_onClick)
{
	onClick = p_onClick;
}

void Button::Release(bool p_trigger)
{
	if (p_trigger) {
		onClick();
	}

	Control::Release(p_trigger);
}

