#include "Texture.h"

#include "Renderer.h"
#include "Surface.h"
#include "Color.h"

#include <SDL2_image/SDL_image.h> // FIXME: should not depend on other framework

#include <exception>

namespace SDL {

Texture::Texture(Texture &&p_texture)
{
	renderer = p_texture.renderer;
	texture = p_texture.texture;
	
	p_texture.texture = nullptr;
}
	
Texture::Texture(const Renderer &p_renderer)
{
	renderer = &p_renderer;
}
	
Texture::Texture(const Renderer &p_renderer, const Surface &p_surface)
: Texture(p_renderer)
{
	Create(p_surface);
}
	
Texture::Texture(const Renderer &p_renderer, SDL_Texture *p_texture)
: Texture(p_renderer)
{
	texture = p_texture;
}
	
Texture::Texture(const Renderer &p_renderer, PixelFormat p_pixelFormat, Access p_access, const Size &size)
: Texture(p_renderer)
{
	texture = SDL_CreateTexture(renderer->renderer, p_pixelFormat, p_access, size.Width, size.Height);

	if (texture == nullptr) {
		throw std::exception();
	}
}
	
Texture::Texture(const Renderer &p_renderer, const std::string &filename)
: Texture(p_renderer)
{
	texture = IMG_LoadTexture(renderer->renderer, filename.c_str());

	if (texture == nullptr) {
		throw std::exception();
	}
}
	
Texture::~Texture()
{
}
	
Texture& Texture::operator =(const Texture &p_texture)
{
	renderer = p_texture.renderer;
	texture = p_texture.texture;
	
	return *this;
}
	
Texture& Texture::operator =(Texture &&p_texture)
{
	renderer = p_texture.renderer;
	texture = p_texture.texture;
	
	p_texture.texture = nullptr;
	
	return *this;
}

void Texture::Create(const Surface &surface)
{
	texture = SDL_CreateTextureFromSurface(renderer->renderer, surface.surface);
}
	
void Texture::Destroy()
{
	SDL_DestroyTexture(texture);

	texture = nullptr;
}

PixelFormat Texture::GetPixelFormat() const
{
	PixelFormat pixelFormat;
	int access;
	Size size;
	
	SDL_QueryTexture(texture, (uint32_t *)&pixelFormat, (int *)&access, &size.Width, &size.Height);
	
	return pixelFormat;
}
	
Texture::Access Texture::GetAccess() const
{
	PixelFormat pixelFormat;
	Access access;
	Size size;
	
	SDL_QueryTexture(texture, (uint32_t *)&pixelFormat, (int *)&access, &size.Width, &size.Height);
	
	return access;
}

void Texture::SetAlphaMod(uint8_t p_alpha)
{
	SDL_SetTextureAlphaMod(texture, p_alpha);
}
	
void Texture::SetBlendMode(BlendMode p_blendMode)
{
	SDL_SetTextureBlendMode(texture, (SDL_BlendMode)p_blendMode);
}
	
void Texture::SetColorMod(const Color &p_color)
{
	SDL_SetTextureColorMod(texture, p_color.R, p_color.G, p_color.B);
}
	
Size Texture::GetSize() const
{
	PixelFormat pixelFormat;
	Access access;
	Size size;
	
	SDL_QueryTexture(texture, (uint32_t *)&pixelFormat, (int *)&access, &size.Width, &size.Height);
	
	return size;
}

void Texture::Update(void *pixels, int pitch)
{
	SDL_UpdateTexture(texture, nullptr, pixels, pitch);
}

}