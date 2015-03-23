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

	list<Animation::Frame> idleFrames;
	idleFrames.push_back(Animation::Frame(0, TimeSpan(100)));
	animations[AnimationType::IDLE].SetFrames(idleFrames);
	
	list<Animation::Frame> runningFrames;
	runningFrames.push_back(Animation::Frame(1, TimeSpan(100)));
	runningFrames.push_back(Animation::Frame(2, TimeSpan(100)));
	runningFrames.push_back(Animation::Frame(3, TimeSpan(100)));
	animations[AnimationType::RUNNING].SetFrames(runningFrames);
	
	list<Animation::Frame> crouchingFrames;
	crouchingFrames.push_back(Animation::Frame(8, TimeSpan(100)));
	animations[AnimationType::CROUCHING].SetFrames(crouchingFrames);
	
	list<Animation::Frame> lookingUpFrames;
	lookingUpFrames.push_back(Animation::Frame(9, TimeSpan(100)));
	animations[AnimationType::LOOKING_UP].SetFrames(lookingUpFrames);

	direction = Direction::RIGHT;
	animation = &animations[AnimationType::IDLE];
}

void Pit::Crouch(bool enable)
{
	crouching = enable;
	if (enable) {
		animation = &animations[AnimationType::CROUCHING];
	}
}

void Pit::LookUp(bool enable)
{
	lookingUp = enable;
	if (enable) {
		animation = &animations[AnimationType::LOOKING_UP];
	}
}

void Pit::SetDirection(Direction p_direction, bool p_moving)
{
	if (p_moving)
	{
		if (!crouching) {
			animation = &animations[AnimationType::RUNNING];
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
	
	renderer->Copy(texture, texturePositions[animation->GetFrame()], Rect(pos, size), direction == Direction::RIGHT ? Renderer::Flip::NONE : Renderer::Flip::HORIZONTAL);
}

