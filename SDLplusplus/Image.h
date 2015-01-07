#pragma once

#include "Surface.h"
#include "Texture.h"

#ifdef __WIN32__
	#include "sdl_image.h"
#else
	#include <SDL2_image/sdl_image.h>
#endif

#include <string>

namespace SDL {

class Renderer;
	
class Image
{
public:
	enum InitFlag
	{
		JPG  = IMG_INIT_JPG,
		PNG  = IMG_INIT_PNG,
		TIF  = IMG_INIT_TIF,
		WEBP = IMG_INIT_WEBP
	};
	
	Image();
	Image(InitFlag initFlags);
	~Image();
	
	void Init(InitFlag initFlags);
	void Quit();
	
	Surface Load(const std::string &filename);
	Texture LoadTexture(const Renderer &renderer, const std::string &filename);
	
	void SavePNG(const Surface *surface, const std::string &filename);
};
	
inline Image::InitFlag operator|(Image::InitFlag a, Image::InitFlag b) { return Image::InitFlag(int(a) | int(b)); }

	
}