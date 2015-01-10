#include "Ball.h"

using namespace SDL;
using namespace std;

Rect Ball::GridRect;

Ball::Ball(Renderer &p_renderer)
{
	defaultSpeed = 100.0f;

	position = Vector2(0, 0);
	speed = Vector2(defaultSpeed, -defaultSpeed);

	size = Size(10, 10);
	
	texture = Texture(p_renderer, PixelFormat::ABGR_8888, Texture::Access::TARGET, size);
	
	auto oldTarget = p_renderer.GetRenderTarget();
	p_renderer.SetRenderTarget(texture);
	p_renderer.SetDrawColor(Color::White);
	p_renderer.FillRect(size);
	p_renderer.SetRenderTarget(oldTarget);
}

void Ball::SetPosition(const SDL::Point &p_position)
{
	position = Vector2(p_position.X, p_position.Y);
}

void Ball::Update(float deltaTime)
{
	previousPosition = position;

	position += speed * deltaTime;
}

void Ball::Collide(const list<Collider *> &colliders)
{
	Rect ballRect(Point(position.x, position.y), size);
	
	for (auto collider : colliders) {
		Rect colliderRect = collider->GetRect();
		Rect collidedRect = colliderRect.Intersect(Rect(Point(position.x, position.y), size));
		if (!collidedRect.IsEmpty()) {
			Direction direction = Direction::NONE;
			
			// determine which side collided
			if (!collidedRect.Intersect(Rect(colliderRect.Position, Size(colliderRect.Size.Width, 2))).IsEmpty()) {
				direction = Direction::DOWN;
			}
			else if (!collidedRect.Intersect(Rect(Point(colliderRect.Position.X, colliderRect.GetBottomRight().Y), Size(colliderRect.Size.Width, 2))).IsEmpty()) {
				direction = Direction::UP;
			}
									   
			collider->OnCollide(direction);
			
			switch (direction)
			{
				case Direction::DOWN:
				case Direction::UP:
					speed.y = -speed.y;
					break;

				case Direction::LEFT:
				case Direction::RIGHT:
					speed.x = -speed.x;
					break;
			}
		}
	}
}

void Ball::Draw(Renderer &p_renderer)
{
	p_renderer.Copy(texture, GridRect.Position + Point((int)position.x, (int)position.y));
}