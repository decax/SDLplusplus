#include "Surface.h"

#include <cassert>

#include "Color.h"
#include "Rect.h"

namespace SDL {

Surface::Surface(PixelFormat p_pixelFormat, const Size &p_size)
{
	int bpp;
	uint32_t rmask, gmask, bmask, amask;
	SDL_PixelFormatEnumToMasks(p_pixelFormat, &bpp, &rmask, &gmask, &bmask, &amask);

	surface = SDL_CreateRGBSurface(0, p_size.Width, p_size.Height, bpp, rmask, gmask, bmask, amask);
}
	
Surface::Surface(SDL_Surface *p_surface)
{
	surface = p_surface;
}
	
Surface::Surface(Surface &&other)
{
	surface = other.surface;
	
	other.surface = nullptr;
}

Surface::~Surface()
{
	SDL_FreeSurface(surface);
}
	
void Surface::ConvertPixelFormat(PixelFormat p_pixelFormat)
{
	auto newSurface = SDL_ConvertSurfaceFormat(surface, p_pixelFormat, 0);
	SDL_FreeSurface(surface);
	surface = newSurface;
}

PixelFormat Surface::GetPixelFormat() const
{
	return (PixelFormat)SDL_MasksToPixelFormatEnum(surface->format->BitsPerPixel,
												   surface->format->Rmask,
												   surface->format->Gmask,
												   surface->format->Bmask,
												   surface->format->Amask);
}
	
Size Surface::GetSize() const
{
	assert(surface);
	
	return Size(surface->w, surface->h);
}
	
Color *Surface::GetColors() const
{
	Color *colors = new Color[surface->w * surface->h];
	
	uint32_t *pixels = (uint32_t *)surface->pixels;
	
	for (int i = 0; i < surface->w * surface->h; i++) {
		colors[i] = pixels[i];
	}
	
	return colors;
}
	
void Surface::SetColors(Color *p_colors)
{
	uint32_t *pixels = (uint32_t *)surface->pixels;

	for (int i = 0; i < surface->w * surface->h; i++) {
		pixels[i] = *(uint32_t *)(Color *)&p_colors[i];
	}
}
	
void Surface::Blit(const Rect &p_srcRect, const Surface &p_dstSurface, const Rect &p_dstRect)
{
	if (p_srcRect.Size == p_dstRect.Size)
	{
		SDL_BlitSurface(surface, (SDL_Rect *)&p_srcRect, p_dstSurface.surface, (SDL_Rect *)&p_dstRect);
	}
	else
	{
		SDL_BlitScaled(surface, (SDL_Rect *)&p_srcRect, p_dstSurface.surface, (SDL_Rect *)&p_dstRect);
	}
}

	
}