#include "TTF.h"

#include <cassert>

namespace SDL {

TTF::TTF()
{
	Init();
}

TTF::~TTF()
{
	Quit();
}
	
void TTF::Init()
{
	TTF_Init();
}
	
void TTF::Quit()
{
	TTF_Quit();
}

TTF::Font::Font()
{
}
	
TTF::Font::Font(const std::string &p_filename, int p_pointSize)
{
	Open(p_filename, p_pointSize);
}
	
TTF::Font::~Font()
{
	TTF_CloseFont(font);
}
	
void TTF::Font::Open(const std::string &p_filename, int p_pointSize)
{
	font = TTF_OpenFont(p_filename.c_str(), p_pointSize);
}
	
void TTF::Font::SetStyle(Style p_style)
{
	assert(font != nullptr);
	
	TTF_SetFontStyle(font, p_style);
}
	
TTF::Font::Style TTF::Font::GetStyle() const
{
	return (Style)TTF_GetFontStyle(font);
}

void TTF::Font::SetOutline(int p_outline)
{
	assert(font != nullptr);
	
	TTF_SetFontOutline(font, p_outline);
}

int TTF::Font::GetOutline() const
{
	assert(font != nullptr);
	
	return TTF_GetFontOutline(font);
}
	
void TTF::Font::SetHinting(Hinting hinting)
{
	assert(font != nullptr);

	TTF_SetFontHinting(font, (int)hinting);
}

TTF::Font::Hinting TTF::Font::GetHinting() const
{
	assert(font != nullptr);
	
	return (Hinting)TTF_GetFontHinting(font);
}
	
int TTF::Font::GetHeight() const
{
	assert(font != nullptr);
	
	return TTF_FontHeight(font);
}

int TTF::Font::GetAscent() const
{
	assert(font != nullptr);
	
	return TTF_FontAscent(font);
}

int TTF::Font::GetDescent() const
{
	assert(font != nullptr);
	
	return TTF_FontDescent(font);
}
	
int TTF::Font::GetLineSkip() const
{
	assert(font != nullptr);
	
	return TTF_FontLineSkip(font);
}
	
bool TTF::Font::IsFixedWidth() const
{
	assert(font != nullptr);
	
	return TTF_FontFaceIsFixedWidth(font);
}
	
std::string TTF::Font::GetFamilyName() const
{
	assert(font != nullptr);
	
	return TTF_FontFaceFamilyName(font);
}

std::string TTF::Font::GetStyleName() const
{
	assert(font != nullptr);
	
	return TTF_FontFaceStyleName(font);
}
	
Size TTF::Font::GetSize(const std::string &p_text) const
{
	assert(font != nullptr);
	
	Size size;
	TTF_SizeText(font, p_text.c_str(), &size.Width, &size.Height);
	
	return size;
}
	
int TTF::Font::GetKerningSize(char p_previousCharacter, char p_character) const
{
	assert(font != nullptr);
	
	return TTF_GetFontKerningSize(font, p_previousCharacter, p_character);
}

Surface TTF::Font::RenderGlyphBlended(char p_character, const Color &p_color)
{
	return Surface(TTF_RenderGlyph_Blended(font, (uint16_t)p_character, *(SDL_Color *)(&p_color)));
}
	
Surface TTF::Font::RenderTextBlended(const std::string &p_text, const Color &p_color)
{
	assert(font != nullptr);
	
	return Surface(TTF_RenderText_Blended(font, p_text.c_str(), *(SDL_Color *)(&p_color)));
}

// FIXME: doesn't work
Surface TTF::Font::RenderTextBlended(const std::wstring &p_text, const SDL::Color &p_color)
{
	assert(font != nullptr);
	
	return Surface(TTF_RenderUNICODE_Blended(font, (uint16_t *)p_text.c_str(), *(SDL_Color *)(&p_color)));
}
	
// Cached glyph version
void TTF::Font::RenderTextBlended(Renderer &p_renderer, const std::string &p_text, const Point &p_position, const Color &p_color)
{
	assert(font != nullptr);
	
	Point position = p_position;

	char previousChararacter = 0;
	
	for (int i = 0; i < p_text.size(); i++) {
		char c = p_text[i];
		
		Texture *texture;
		
		auto it = glyphTextures.find(c);
		if (it == glyphTextures.end()) {
			// add the glyph
			glyphTextures[c] = Texture(p_renderer, RenderGlyphBlended(c, p_color));
			texture = &glyphTextures[c];
		}
		else {
			texture = &it->second;
		}
		
		position.X += i == 0 ? 0 : /*GetKerningSize(previousChararacter, c)*/glyphTextures[previousChararacter].GetSize().Width;
		previousChararacter = c;
		
		p_renderer.Copy(*texture, position);
	}
}
	
}