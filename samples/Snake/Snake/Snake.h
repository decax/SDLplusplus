#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include "Player.h"

class Piece;

class Snake
{
public:
	Snake();
	
	void Run();
	
private:
	void StartGame();
	
	SDL::System system;
	SDL::Window window;
	SDL::Renderer renderer;
	
	SDL::Size gridSize;
	SDL::Point gridPosition;
	
	Player player;
	
	SDL::Point food;
	
	static const int GRID_WIDTH_IN_SQUARES  = 32;
	static const int GRID_HEIGHT_IN_SQUARES = 32;
	
	SDL::Size gridSizeInSquares;
	
	bool running;
	
	static const int updateDelay = 100;
	int nextUpdate;
};