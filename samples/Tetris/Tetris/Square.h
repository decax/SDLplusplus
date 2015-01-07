#pragma once

#include <SDLplusplus/SDLplusplus.h>

class Square
{
public:
	static const int Width = 32;
	static const int Height = 32;
	
	static void CreateTextures(SDL::Renderer &renderer);
	
	static void Draw(SDL::Renderer &renderer, const SDL::Color &color, const SDL::Point &position);
	
private:
	static void DrawTexture(SDL::Renderer &renderer);
	static SDL::Texture texture;
};
