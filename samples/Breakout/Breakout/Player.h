#pragma once

#include "Vector2.h"
#include "Direction.h"

#include <SDLplusplus/SDLplusplus.h>

class Player
{
public:
	Player(SDL::Renderer &renderer);
	
	void Update(float deltaTime);
	void Draw(SDL::Renderer &renderer);
	
	SDL::Rect GetRect() const;
	
	void SetPosition(const SDL::Point &position);
	void SetDirection(Direction direction);
	
	static SDL::Point GridPosition;
	
	static const int Width = 100;
	static const int Height = 20;
	
private:
	SDL::Texture texture;
	
	Vector2 position;
	SDL::Size size;
	
	Direction direction;
	float speed;
};