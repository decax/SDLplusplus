#pragma once

#include "SDL.h"

#include <SDL2_ttf/SDL_ttf.h>

#include <string>

namespace SDL {
	
class TTF
{
public:
	TTF();
	~TTF();
	
	class Font
	{
	public:
		enum Style
		{
			NORMAL         = TTF_STYLE_NORMAL,
			BOLD           = TTF_STYLE_BOLD,
			ITALIC         = TTF_STYLE_ITALIC,
			UNDERLINE      = TTF_STYLE_UNDERLINE,
			STRIKE_THROUGH = TTF_STYLE_STRIKETHROUGH
		};
		
		enum class Hinting
		{
			NORMAL = TTF_HINTING_NORMAL,
			LIGHT  = TTF_HINTING_LIGHT,
			MONO   = TTF_HINTING_MONO,
			NONE   = TTF_HINTING_NONE
		};
		
		Font(const std::string &file, int pointSize);
		~Font();
		
		void Open(const std::string &file, int pointSize);

		void SetStyle(Style style);
		Style GetStyle() const;
		void SetOutline(int outline);
		int GetOutline() const;
		
		void SetHinting(Hinting hinting);
		Hinting GetHinting() const;
		
		bool IsFixedWidth() const;
		std::string GetFamilyName() const;
		std::string GetStyleName() const;
		
		Surface RenderTextBlended(const std::string &text, const SDL::Color &color);
		Surface RenderTextBlended(const std::wstring &text, const SDL::Color &color);
		
	private:
		TTF_Font *font;
	};
	
	static void Init();
	static void Quit();
};
	
	inline TTF::Font::Style operator|(TTF::Font::Style a, TTF::Font::Style b) { return TTF::Font::Style(int(a) | int(b)); }

	
}