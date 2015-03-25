#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include "Animation.h"

#include "Time.h"
#include "Type.h"

class Snake
{
public:
	Snake(SDL::Renderer &renderer);
	
	void Update(const Time &time);
	void Draw();
	
private:
	SDL::Renderer *renderer;
	
	Direction direction;
	
	SDL::Size size;
	
	Vector2 position;
	
	SDL::Texture texture;
	SDL::Rect *texturePositions;

	Animation *animation;
	Animation animations[1];
};