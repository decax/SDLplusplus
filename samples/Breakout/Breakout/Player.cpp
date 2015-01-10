#include "Player.h"

#include "Square.h"

using namespace SDL;

Point Player::GridPosition;

Player::Player(Renderer &p_renderer)
{
	position = Vector2(0.0f, 350.0f);
	size = Size(Width, Height);
	speed = 400;
	
	texture = Texture(p_renderer, PixelFormat::ABGR_8888, Texture::Access::TARGET, size);

	auto oldTarget = p_renderer.GetRenderTarget();
	p_renderer.SetRenderTarget(texture);
	p_renderer.SetDrawColor(Color::Gray);
	p_renderer.FillRect(size);
	p_renderer.SetRenderTarget(oldTarget);
	
	direction = Direction::NONE;
}

void Player::Update(float deltaTime)
{
	switch (direction)
	{
		case Direction::LEFT:  position.x -= speed * deltaTime; break;
		case Direction::RIGHT: position.x += speed * deltaTime; break;

		default:
			break;
	}
}

void Player::Draw(Renderer &p_renderer)
{
	p_renderer.Copy(texture, GridPosition + Point((int)position.x, (int)position.y));
}

void Player::SetPosition(const Point &p_position)
{
	position = Vector2(p_position.X, p_position.Y);
}

void Player::SetDirection(Direction p_direction)
{
	direction = p_direction;
}

Rect Player::GetRect() const
{
	return Rect(Point((int)position.x, (int)position.y), size);
}
