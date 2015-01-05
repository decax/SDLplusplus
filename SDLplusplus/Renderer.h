#pragma once

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <iostream>

#include "Rect.h"

#include "Texture.h"

namespace SDL {

class Window;
class Rect;
class Color;

class Renderer
{
	friend class Texture;
	
public:
	enum TypeFlag
	{
		SOFTWARE       = SDL_RENDERER_SOFTWARE,
		ACCELERATED    = SDL_RENDERER_ACCELERATED,
		PRESENT_VSYNC  = SDL_RENDERER_PRESENTVSYNC,
		TARGET_TEXTURE = SDL_RENDERER_TARGETTEXTURE
	};
	
	class Info
	{
		friend class Renderer;

	public:
		std::vector<uint32_t> TextureFormats;
		
		const std::string &GetName() const;
		Renderer::TypeFlag GetTypeFlags() const;
		const Size &GetMaxTextureSize() const;
		
	private:
		Info(const std::string &name, Renderer::TypeFlag flags, uint32_t numTextureFormat, uint32_t *textureFormats, const Size &maxTextureSize);
		
		std::string name;
		Renderer::TypeFlag flags;
		Size maxTextureSize;
	};
	
	Renderer(const Window &window, TypeFlag type);
	~Renderer();
	
	void Present();
	void Clear();
	
	Size GetOutputSize() const;
	
	void SetClipRect(const Rect &rect); // FIXME: doesn't work
	Rect GetClipRect() const;
	
	Texture GetRenderTarget() const;
	void SetRenderTarget(const Texture &texture);
	
	enum Flip
	{
		NONE       = SDL_FLIP_NONE,
		HORIZONTAL = SDL_FLIP_HORIZONTAL,
		VERTICAL   = SDL_FLIP_VERTICAL
	};

	void Copy(const Texture &texture);
	void Copy(const Texture &texture, Flip flip);
	void Copy(const Texture &texture, double angle, Flip flip);
	void Copy(const Texture &texture, double angle, const Point &center, Flip flip);

	void Copy(const Texture &texture, const Point &dstPosition);
	
	void Copy(const Texture &texture, const Rect &destRect);
	void Copy(const Texture &texture, const Rect &srcRect, const Rect &dstRect);
	
	void Copy(const Texture &texture, double angle);
	void Copy(const Texture &texture, double angle, const Point &center);
	void Copy(const Texture &texture, const Rect &dstRect, double angle);
	void Copy(const Texture &texture, const Rect &dstRect, double angle, const Point &center);
	void Copy(const Texture &texture, const Rect &srcRect, const Rect &dstRect, double angle);
	void Copy(const Texture &texture, const Rect &srcRect, const Rect &dstRect, double angle, const Point &center);
	void Copy(const Texture &texture, const Rect &srcRect, const Rect &dstRect, double angle, const Point &center, Flip flip);
	
	// Drawing methods
	void SetDrawColor(const Color &color);
	void DrawPoint(const Point &position);
	void DrawLine(const Point &startPosition, const Point &endPosition);
	void DrawRect(const Rect &rect);
	void FillRect(const Rect &rect);
	
	Info GetInfo();
	
	void SetWindow(const Window &window);

	SDL_Renderer *GetSDLRenderer() const;
	
private:
	const Window *window;
	
	SDL_Renderer *renderer;
};

inline const std::string &Renderer::Info::GetName() const
{
	return name;
}
	
inline Renderer::TypeFlag Renderer::Info::GetTypeFlags() const
{
	return flags;
}
	
inline const Size &Renderer::Info::GetMaxTextureSize() const
{
	return maxTextureSize;
}

inline void Renderer::Copy(const Texture &p_texture, Flip p_flip)
{
	Copy(p_texture, p_texture.GetSize(), GetOutputSize(), 0, p_texture.GetSize().Center(), p_flip);
}
	
inline void Renderer::Copy(const Texture &p_texture, double p_angle, Flip p_flip)
{
	Copy(p_texture, p_texture.GetSize(), GetOutputSize(), p_angle, p_texture.GetSize().Center(), p_flip);
}

inline void Renderer::Copy(const Texture &p_texture, double p_angle, const Point &p_center, Flip p_flip)
{
	Copy(p_texture, p_texture.GetSize(), GetOutputSize(), p_angle, p_center, p_flip);
}

inline void Renderer::Copy(const Texture &p_texture, const Point &p_dstPosition)
{
	Rect textureRect(p_texture.GetSize());
	
	Copy(p_texture, textureRect, textureRect + p_dstPosition);
}
	
inline void Renderer::Copy(const Texture &p_texture, const Rect &p_destRect)
{
	Rect textureRect(p_texture.GetSize());
	
	Copy(p_texture, textureRect, p_destRect);
}

inline void Renderer::Copy(const Texture &p_texture, double p_angle)
{
	Copy(p_texture, p_angle, p_texture.GetSize().Center());
}
	
inline void Renderer::Copy(const Texture &p_texture, const Rect &p_dstRect, double p_angle)
{
	Rect textureRect(p_texture.GetSize());
	
	Copy(p_texture, textureRect, p_dstRect, p_angle, p_texture.GetSize().Center());
}

inline void Renderer::Copy(const Texture &p_texture, const Rect &p_dstRect, double p_angle, const Point &p_center)
{
	Rect textureRect(p_texture.GetSize());
	
	Copy(p_texture, textureRect, p_dstRect, p_angle, p_center);
}
	
inline void Renderer::Copy(const Texture &p_texture, const Rect &p_srcRect, const Rect &p_dstRect, double p_angle, const Point &p_center)
{
	Copy(p_texture, p_srcRect, p_dstRect, p_angle, p_center, Flip::NONE);
}

inline Renderer::TypeFlag operator|(Renderer::TypeFlag a, Renderer::TypeFlag b) { return Renderer::TypeFlag(int(a) | int(b)); }
inline Renderer::Flip operator|(Renderer::Flip a, Renderer::Flip b) { return Renderer::Flip(int(a) | int(b)); }
	
}