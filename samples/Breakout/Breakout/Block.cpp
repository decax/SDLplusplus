#include "Block.h"

using namespace SDL;

Texture Block::texture;
Point Block::GridPosition;

Block::Block(const Point &p_position, const Color &p_color)
{
	position = p_position;
	color = p_color;
	
	dead = false;
}

void Block::Draw(Renderer &p_renderer)
{
	texture.SetColorMod(color);
	p_renderer.Copy(texture, GridPosition + position);
}

void Block::OnCollide(Direction p_direction)
{
	dead = true;
}

bool Block::IsDead() const
{
	return dead;
}

Rect Block::GetRect() const
{
	return Rect(position, Size(Width, Height));
}

void Block::CreateTexture(SDL::Renderer &p_renderer)
{
	texture = Texture(p_renderer, PixelFormat::ABGR_8888, Texture::Access::TARGET, Size(Width, Height));
	
	auto oldTarget = p_renderer.GetRenderTarget();
	
	DrawTexture(p_renderer);
	
	p_renderer.SetRenderTarget(oldTarget);
	p_renderer.SetDrawColor(SDL::Color::Black);
}

void Block::DrawTexture(Renderer &p_renderer)
{
	Size size = texture.GetSize();
	
	SDL::Color color = SDL::Color::White;
	
	p_renderer.SetRenderTarget(texture);
	p_renderer.SetDrawColor(color);
	p_renderer.FillRect(Rect(size));
	
	p_renderer.SetDrawColor(color.Lighten(0.25f));
	p_renderer.DrawLine(Point(0, 0), Point(size.Width - 1, 0));
	p_renderer.DrawLine(Point(0, 0), Point(0, size.Height - 1));
	
	p_renderer.SetDrawColor(color.Darken(0.25f));
	p_renderer.DrawLine(Point(size.Width - 1, 1), Point(size.Width - 1, size.Height - 1));
	p_renderer.DrawLine(Point(1, size.Height - 1), Point(size.Width - 2, size.Height - 1));
}
