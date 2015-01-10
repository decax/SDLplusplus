#pragma once

#include "Direction.h"

#include <SDLplusplus/SDLplusplus.h>

class Collider
{
public:
	virtual ~Collider() {}
	
	virtual SDL::Rect GetRect() const = 0;
	virtual void OnCollide(Direction direction) {}
};
