#include "Image.h"

#include "SDLplusplus.h"

namespace SDL {

Image::Image()
: Image(InitFlag::JPG | InitFlag::PNG | InitFlag::TIF | InitFlag::WEBP)
{
}
	
Image::Image(InitFlag initFlags)
{
	Init(initFlags);
}
	
Image::~Image()
{
	Quit();
}
	
void Image::Init(InitFlag initFlags)
{
	IMG_Init(initFlags);
}
	
void Image::Quit()
{
	IMG_Quit();
}
	
Surface Image::Load(const std::string &p_filename)
{
	return Surface(IMG_Load(p_filename.c_str()));
}
	
Texture Image::LoadTexture(const Renderer &p_renderer, const std::string &p_filename)
{
	return Texture(p_renderer, IMG_LoadTexture(p_renderer.GetSDLRenderer(), p_filename.c_str()));
}
	
void Image::SavePNG(const Surface &p_surface, const std::string &p_filename)
{
	IMG_SavePNG(p_surface.surface, p_filename.c_str());
}

	
}