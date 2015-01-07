#pragma once

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

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