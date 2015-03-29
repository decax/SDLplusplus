#pragma once

#include "TMX.h"

#include <SDLplusplus/SDLplusplus.h>

class Level
{
public:
	Level(SDL::Renderer &renderer);
	
	void Load();
	
	void Draw();
	
private:
	SDL::Renderer *renderer;
	SDL::Texture tileset;
	
	TMX tmx;
	
	SDL::Rect *tileRects;
};