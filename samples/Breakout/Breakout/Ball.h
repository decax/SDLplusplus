#pragma once

#include "Vector2.h"
#include "Collider.h"

#include <SDLplusplus/SDLplusplus.h>

#include <list>

class Ball
{
public:
	Ball(SDL::Renderer &renderer);
	
	void SetPosition(const SDL::Point &position);
	
	void Update(float deltaTime);
	void Draw(SDL::Renderer &renderer);
	
	static SDL::Rect GridRect;
	
	void Collide(const std::list<Collider *> &colliders); // check for collisions and adjust position accordingly
	
private:
	SDL::Texture texture;
	
	SDL::Size size;
	
	Vector2 position;
	Vector2 speed;
	
	float defaultSpeed;
	
	Vector2 previousPosition; // used when colliding
};