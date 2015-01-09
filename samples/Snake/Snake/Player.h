#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include <list>

class Player
{
public:
	enum Direction {
		UP, DOWN, LEFT, RIGHT
	};
	
	Player();
	
	void Update();
	void Draw(SDL::Renderer &renderer);
	
	static SDL::Point GridPosition;
	
	void SetDirection(Direction direction);
	
	SDL::Point GetHead() const; // hehe
	
	void Grow(int size);
	bool EatsHimself() const;
	
private:
	std::list<SDL::Point> body;
	
	Direction direction;

	int toGrow;
};