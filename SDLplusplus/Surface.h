#pragma once

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include "Size.h"
#include "Rect.h"
#include "PixelFormat.h"

namespace SDL {

class Color;
	
class Surface
{
	friend class Texture;
	
public:
	enum Flag
	{
		SOFTWARE        = SDL_SWSURFACE,
		PRE_ALLOCATED   = SDL_PREALLOC,
		RLE_ACCELERATED = SDL_RLEACCEL,
		DONT_FREE       = SDL_DONTFREE
	};
	
	Surface();
	Surface(const Surface &surface);
	Surface(Surface &&other);
	Surface(PixelFormat pixelFormat, const Size &size);
	Surface(SDL_Surface *surface);
	~Surface();
	
	const Surface &operator =(const Surface &surface);
	const Surface &operator =(Surface &&surface);
	
	void ConvertPixelFormat(PixelFormat pixelFormat);
	PixelFormat GetPixelFormat() const;
	
	Size GetSize() const;
	
	Color *GetColors() const;
	void SetColors(Color *colors);
	
	void Blit(const Surface &dstSurface);
	void Blit(const Surface &dstSurface, const Rect &dstRect);
	void Blit(const Rect &srcRect, const Surface &dstSurface, const Rect &dstRect);
	
//private:
	SDL_Surface *surface;
};

inline void Surface::Blit(const Surface &dstSurface)
{
	Blit(Rect(Point(0, 0), GetSize()), dstSurface, dstSurface.GetSize());
}

inline void Surface::Blit(const Surface &dstSurface, const Rect &dstRect)
{
	Blit(Rect(Point(0, 0), GetSize()), dstSurface, dstRect);
}
	
}