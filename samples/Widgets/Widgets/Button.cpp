#include "Button.h"

using namespace SDL;
using namespace std;

Button::Button(Renderer &p_renderer)
: renderer(p_renderer)
{
	size = Size(150, 20);
	
	textures[0] = Texture(renderer, PixelFormat::ARGB_8888, Texture::Access::TARGET, size);
	textures[1] = Texture(renderer, PixelFormat::ARGB_8888, Texture::Access::TARGET, size);
	
	auto oldTarget = renderer.GetRenderTarget();
	renderer.SetRenderTarget(textures[0]);
	renderer.SetDrawColor(Color::Gray);
	renderer.FillRect(size);
	renderer.SetRenderTarget(oldTarget);
}

void Button::SetPosition(const Point &p_position)
{
	position = p_position;
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
	renderer.Copy(textures[0], position);
	label.Draw(renderer);
}

