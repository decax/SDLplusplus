#include "Pit.h"

#include <SDLplusplus/Image.h>

using namespace SDL;
using namespace std;

Pit::Pit(Renderer &p_renderer)
{
	renderer = &p_renderer;
	
	position = Vector2(0, 300);
	speed = Vector2(0, 0);
	
	defaultSpeed = Vector2(80.0f, 0.f);

	size = Size(16, 24);
	
	texture = Image::LoadTexture(*renderer, "Pit.png");
	texturePositions = new Rect[4 * 3];
	int index = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 4; x++) {
			texturePositions[index++] = Rect(Point(x * size.Width, y * size.Height), size);
		}
	}

	animations[AnimationType::IDLE      ].SetFrames("0");
	animations[AnimationType::RUNNING   ].SetFrames("Delay:100 1 2 3");
	animations[AnimationType::CROUCHING ].SetFrames("8");
	animations[AnimationType::LOOKING_UP].SetFrames("9");
	
	direction = Direction::RIGHT;
	SetAnimation(AnimationType::IDLE);
}

void Pit::Crouch(bool enable)
{
	crouching = enable;
	if (enable) {
		SetAnimation(AnimationType::CROUCHING);
	}
}

void Pit::LookUp(bool enable)
{
	lookingUp = enable;
	if (enable) {
		SetAnimation(AnimationType::LOOKING_UP);
	}
}

void Pit::SetAnimation(AnimationType animationType)
{
	animation = &animations[animationType];
}

void Pit::SetDirection(Direction p_direction, bool p_moving)
{
	if (p_moving)
	{
		if (!crouching) {
			SetAnimation(AnimationType::RUNNING);
		}

		if (!lookingUp) {
			switch (p_direction)
			{
				case Direction::LEFT:  direction = p_direction; speed = defaultSpeed * Vector2(-1, 0); break;
				case Direction::RIGHT: direction = p_direction; speed = defaultSpeed; break;
					
				default:
					// don't care
					break;
			}
		}
	}
	else
	{
		animation = &animations[AnimationType::IDLE];
		speed = Vector2(0, 0);
	}
}

void Pit::Update(const Time &time)
{
	animation->Update(time);
	
	position += speed * time.GetDelta().GetTotalSeconds();
}

void Pit::Draw()
{
	Point pos((int)position.x, (int)position.y);
	
	renderer->Copy(texture, texturePositions[animation->GetFrame().index], Rect(pos, size), direction == Direction::RIGHT ? Renderer::Flip::NONE : Renderer::Flip::HORIZONTAL);
}

