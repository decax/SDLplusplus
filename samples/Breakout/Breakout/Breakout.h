#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include "Player.h"
#include "Ball.h"
#include "Block.h"

#include <list>

class Collider;

class Breakout
{
public:
	Breakout();
	
	void Run();
	
private:
	void StartGame();
	void OnKeyDown(const SDL::Event &event);
	
	SDL::System system;
	SDL::Window window;
	SDL::Renderer renderer;
	
	SDL::Size gridSize;
	SDL::Point gridPosition;
	
	Player player;
	Ball ball;
	
	static const int GRID_WIDTH_IN_BLOCKS  = 12;
	static const int GRID_HEIGHT_IN_BLOCKS = 16;
	
	SDL::Size gridSizeInSquares;
	
	bool running;
	
	int lastTime;
	
	std::list<Block> blocks;
	
	static const int updateDelay = 25;
	int nextUpdate;
};