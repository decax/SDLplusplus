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

	
}