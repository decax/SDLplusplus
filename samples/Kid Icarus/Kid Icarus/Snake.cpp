#include "Snake.h"

#include <SDLplusplus/Image.h>

#include <list>
#include <iostream>

using namespace SDL;
using namespace std;

Snake::Snake(Renderer &p_renderer)
{
	renderer = &p_renderer;
	
	position = Vector2(0, 0);
	
	direction = Direction::RIGHT;
	
	texture = Image::LoadTexture(*renderer, "Snake.png");

	size = Size(16, 24);
	
	texturePositions = new Rect[2];
	int index = 0;
	for (int y = 0; y < 1; y++) {
		for (int x = 0; x < 2; x++) {
			texturePositions[index++] = Rect(Point(x * size.Width, y * size.Height), size);
		}
	}
	
	animations[0].SetFrames("Delay:100 0 1");

	animation = &animations[0];
}

void Snake::Update(const Time &time)
{
	animation->Update(time);
}

void Snake::Draw()
{
	Point pos((int)position.x, (int)position.y);
	
	renderer->Copy(texture, texturePositions[animation->GetFrame().index], Rect(pos, size), direction == Direction::RIGHT ? Renderer::Flip::NONE : Renderer::Flip::HORIZONTAL);
}