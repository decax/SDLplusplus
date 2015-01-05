#include "Surface.h"

namespace SDL {

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

}