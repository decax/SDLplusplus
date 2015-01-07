#pragma once

#ifdef __WIN32__
	#include "SDL_ttf.h"
#else
	#include <SDL2_ttf/SDL_ttf.h>
#endif

#include <string>
#include <map>

#include "SDLplusplus.h"

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
		
		Font();
		Font(const std::string &file, int pointSize);
		~Font();
		
		void Open(const std::string &file, int pointSize);

		bool IsFixedWidth() const;
		std::string GetFamilyName() const;
		std::string GetStyleName() const;
		
		void SetStyle(Style style);
		Style GetStyle() const;
		void SetOutline(int outline);
		int GetOutline() const;
		
		void SetHinting(Hinting hinting);
		Hinting GetHinting() const;
		
		int GetHeight() const;
		int GetAscent() const;
		int GetDescent() const;
		int GetLineSkip() const;
		
		int GetKerningSize(char previousCharacter, char character) const;

		Size GetSize(const std::string &text) const;
		
		Surface RenderGlyphBlended(char character, const Color &color);
		Surface RenderTextBlended(const std::string &text, const SDL::Color &color);
		Surface RenderTextBlended(const std::wstring &text, const SDL::Color &color);
		
		void RenderTextBlended(Renderer &renderer, const std::string &text, const Point &position);
		
	private:
		TTF_Font *font;
		
		std::map<char, Texture> glyphTextures;
	};
	
	static void Init();
	static void Quit();
};
	
inline TTF::Font::Style operator|(TTF::Font::Style a, TTF::Font::Style b) { return TTF::Font::Style(int(a) | int(b)); }

	
}