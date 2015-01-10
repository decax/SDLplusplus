#pragma once

#include <SDLplusplus/SDLplusplus.h>

#include "Collider.h"

class Block : public Collider
{
public:
	Block(const SDL::Point &position, const SDL::Color &color);
	
	void Draw(SDL::Renderer &renderer);
	
	static SDL::Point GridPosition;
	static void CreateTexture(SDL::Renderer &p_renderer);

	static const int Width = 64;
	static const int Height = 32;
	
	bool IsDead() const;

private:
	SDL::Point position;
	SDL::Color color;
	
	static void DrawTexture(SDL::Renderer &renderer);
	static SDL::Texture texture;
	
	void OnCollide(Direction direction);
	SDL::Rect GetRect() const;
	
	bool dead;
};
