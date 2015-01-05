#pragma once

#include <SDLplusplus/SDL.h>

class Piece
{
public:
	enum Shape
	{
		L, J, T, Z, S, I, O
	};
	
	static const int NB_SHAPES = 7;
	
	static const int Width = 32;
	static const int Height = 32;
	
	static const SDL::Color *colors[NB_SHAPES];
	
	static void CreateTextures(SDL::Renderer &renderer);
	
	Piece(Shape shape);
	
	void Draw(SDL::Renderer &renderer);
	
	SDL::Point Position;
	SDL::Rect GetBounds() const;
	
	void Rotate();
	
	void Deactivate(bool grid[10][17]);
	
	bool Collide(bool grid[10][17], SDL::Point position) const;

	static SDL::Point GridPosition;
	
private:
	static const int bufferWidth = 4;
	static const int bufferHeight = 4;
	
	bool buffer[bufferWidth][bufferHeight];
	
	Shape shape;
	int rotation;
	
	void UpdateShapeMask();

	static int shapeMasks[NB_SHAPES][4][bufferHeight][bufferWidth];
};