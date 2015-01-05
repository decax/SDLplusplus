#include "Renderer.h"

#include "Window.h"
#include "Texture.h"
#include "Rect.h"
#include "Color.h"

#include <cassert>
#include <exception>

namespace SDL {

Renderer::Renderer(const Window &p_window, TypeFlag type)
{
	SetWindow(p_window);
	
	renderer = SDL_CreateRenderer(window->window, -1, type);
	if (renderer == nullptr) {
		throw std::exception();
	}
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}

void Renderer::Clear()
{
	assert(renderer != nullptr);
	
	SDL_RenderClear(renderer);
}

void Renderer::Present()
{
	assert(renderer != nullptr);
	
	SDL_RenderPresent(renderer);
}
	
Texture Renderer::GetRenderTarget() const
{
	return Texture(*this, SDL_GetRenderTarget(renderer));
}

void Renderer::SetRenderTarget(const Texture &texture)
{
	if (SDL_SetRenderTarget(renderer, texture.texture) != 0) {
		// error
	}
}
	
void Renderer::SetClipRect(const Rect &rect)
{
	SDL_RenderSetClipRect(renderer, (const SDL_Rect *)&rect);
}
	
Rect Renderer::GetClipRect() const
{
	Rect rect;
	
	SDL_RenderGetClipRect(renderer, (SDL_Rect *)&rect);
	
	return rect;
}
	
Size Renderer::GetOutputSize() const
{
	Size size;
	
	SDL_GetRendererOutputSize(renderer, &size.Width, &size.Height);
	
	return size;
}

void Renderer::Copy(const Texture &p_texture)
{
	SDL_RenderCopy(renderer, p_texture.texture, nullptr, nullptr);
}

void Renderer::Copy(const Texture &p_texture, const Rect &p_sourceRect, const Rect &p_destRect)
{
	SDL_RenderCopy(renderer, p_texture.texture, (const SDL_Rect *)&p_sourceRect, (const SDL_Rect *)&p_destRect);
}
	
void Renderer::Copy(const Texture &p_texture, double p_angle, const Point &p_center)
{
	SDL_RenderCopyEx(renderer, p_texture.texture, nullptr, nullptr, p_angle, (const SDL_Point *)&p_center, SDL_FLIP_NONE);
}
	
void Renderer::Copy(const Texture &p_texture, const Rect &p_srcRect, const Rect &p_dstRect, double p_angle, const Point &p_center, Flip p_flip)
{
	SDL_RenderCopyEx(renderer, p_texture.texture, (const SDL_Rect *)&p_srcRect, (const SDL_Rect *)&p_dstRect, p_angle, (const SDL_Point *)&p_center, (SDL_RendererFlip)p_flip);
}

Renderer::Info Renderer::GetInfo()
{
	SDL_RendererInfo info;
	
	SDL_GetRendererInfo(renderer, &info);
	
	return Info(info.name, (TypeFlag)info.flags, info.num_texture_formats, info.texture_formats, Size(info.max_texture_width, info.max_texture_height));
}
	
void Renderer::SetWindow(const Window &p_window)
{
	window = &p_window;
}

void Renderer::SetDrawColor(const Color &p_color)
{
	SDL_SetRenderDrawColor(renderer, p_color.R, p_color.G, p_color.B, p_color.A);
}
	
void Renderer::DrawPoint(const Point &p_position)
{
	SDL_RenderDrawPoint(renderer, p_position.X, p_position.Y);
}
	
void Renderer::DrawLine(const Point &p_startPosition, const Point &p_endPosition)
{
	SDL_RenderDrawLine(renderer, p_startPosition.X, p_startPosition.Y, p_endPosition.X, p_endPosition.Y);
}
	
void Renderer::DrawRect(const Rect &rect)
{
	SDL_RenderDrawRect(renderer, (const SDL_Rect *)&rect);
}

void Renderer::FillRect(const Rect &rect)
{
	SDL_RenderFillRect(renderer, (const SDL_Rect *)&rect);
}
	
Renderer::Info::Info(const std::string &p_name, TypeFlag p_flags, uint32_t p_numTextureFormat, uint32_t *p_textureFormats, const Size &p_maxTextureSize)
: name(p_name)
{
	flags = p_flags;
	maxTextureSize = p_maxTextureSize;
	
	TextureFormats.reserve(p_numTextureFormat);
	for (int i = 0; i < p_numTextureFormat; i++) {
		TextureFormats.push_back(p_textureFormats[i]);
	}
}

SDL_Renderer *Renderer::GetSDLRenderer() const
{
	return renderer;
}

}

