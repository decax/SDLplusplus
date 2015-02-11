#pragma once

#include <SDLplusplus/SDLplusplus.h>

class Piece;

class Tetris
{
public:
	Tetris();
	
	void Run();

private:
	void StartGame();
	void OnKeyDown(const SDL::Event &event);
	
	Piece *GetNextPiece();
	void MovePieceDown();
	void CheckForCompleteLine();

	SDL::System system;
	SDL::Window window;
	SDL::Renderer renderer;
	
	SDL::Size gridSize;
	SDL::Point gridPosition;
	
	static const int GRID_WIDTH_IN_SQUARES  = 10;
	static const int GRID_HEIGHT_IN_SQUARES = 17;
	
	SDL::Size gridSizeInSquares;
	bool grid[GRID_WIDTH_IN_SQUARES][GRID_HEIGHT_IN_SQUARES];
	
	Piece *piece, *nextPiece;
	
	bool running;
	
	static const int updateDelay = 1000;
	int nextUpdate;
};