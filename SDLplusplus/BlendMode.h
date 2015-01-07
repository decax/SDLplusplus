#pragma once

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

enum BlendMode
{
	NONE  = SDL_BLENDMODE_NONE,
	BLEND = SDL_BLENDMODE_BLEND,
	ADD   = SDL_BLENDMODE_ADD,
	MOD   = SDL_BLENDMODE_MOD
};