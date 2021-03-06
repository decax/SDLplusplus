#pragma once

#include "Size.h"
#include "PixelFormat.h"
#include "BlendMode.h"

#ifdef __WIN32__
	#include "SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

#include <string>

namespace SDL {

class Renderer;
class Surface;
class Color;
	
class Texture
{
	friend Renderer;
	
public:
	enum Access
	{
		STATIC    = SDL_TEXTUREACCESS_STATIC,
		STREAMING = SDL_TEXTUREACCESS_STREAMING,
		TARGET    = SDL_TEXTUREACCESS_TARGET
	};
	
	Texture();
	Texture(const Texture &texture);
	Texture(Texture &&texture);
	Texture(Renderer &renderer);
	Texture(Renderer &renderer, const Surface &surface);
	Texture(Renderer &renderer, PixelFormat pixelFormat, Access access, const Size &size);
	Texture(Renderer &renderer, const std::string &filename);
	Texture(Renderer &renderer, SDL_Texture *texture); // fixme: this shouldn't be public
	~Texture();
	
	Texture& operator =(const Texture &texture);
	Texture& operator =(Texture &&texture);
	
	void Create(const Surface &surface);
	void Destroy();
	
	void Update(void *pixels, int pitch);
	
	Size GetSize() const;
	PixelFormat GetPixelFormat() const;
	Access GetAccess() const;
	
	void SetAlphaMod(uint8_t alpha); // TODO: should use float instead
	void SetBlendMode(BlendMode blendMode);
	void SetColorMod(const Color &color);
	
private:
	Renderer *renderer;
	
	SDL_Texture *texture;
};

}