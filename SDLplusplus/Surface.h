#pragma once

#include <SDL2/SDL.h>

namespace SDL {

class Surface
{
	friend class Texture;
	
public:
	Surface(SDL_Surface *surface);
	Surface(Surface &&other);
	~Surface();
	
private:
	SDL_Surface *surface;
};

}