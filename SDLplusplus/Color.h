#pragma once

#include <SDL2/SDL.h>

#include <algorithm>

namespace SDL {

class Color
{
public:
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	
	Color(uint32_t hexCode);
	
	Color Darken(float percentage) const;
	Color Lighten(float percentage) const;
	
	uint8_t R, G, B, A;
	
	static Color AliceBlue;
	static Color AntiqueWhite;
	static Color Aqua;
	static Color AquaMarine;
	static Color Azure;
	static Color Beige;
	static Color Bisque;
	static Color Black;
	static Color BlanchedAlmond;
	static Color Blue;
	static Color BlueViolet;
	static Color Brown;
	static Color BurlyWood;
	static Color CadetBlue;
	static Color Chartreuse;
	static Color Chocolate;
	static Color Coral;
	static Color CornflowerBlue;
	static Color Cornsilk;
	static Color Crimson;
	static Color Cyan;
	static Color DarkBlue;
	static Color DarkCyan;
	static Color DarkGoldenrod;
	static Color DarkGray;
	static Color DarkGreen;
	static Color DarkKhaki;
	static Color DarkMagenta;
	static Color DarkOliveGreen;
	static Color DarkOrange;
	static Color DarkOrchid;
	static Color DarkRed;
	static Color DarkSalmon;
	static Color DarkSeaGreen;
	static Color DarkSlateBlue;
	static Color DarkSlateGray;
	static Color DarkTurquoise;
	static Color DarkViolet;
	static Color DeepPink;
	// to be continued...
	
	static Color White;
	static Color Red;
	static Color Green;
	static Color Magenta;
	static Color Gray;
};
	
inline Color::Color(uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a)
{
	R = p_r;
	G = p_g;
	B = p_b;
	A = p_a;
}

inline Color::Color(uint8_t p_r, uint8_t p_g, uint8_t p_b)
: Color(p_r, p_g, p_b, 0xff)
{
}
	
inline Color::Color(uint32_t hexCode)
: Color((uint8_t)((hexCode & 0x00ff0000) >> 16), (uint8_t)((hexCode & 0x0000ff00) >> 8), (uint8_t)((hexCode & 0x000000ff)))
{
}

inline Color::Color(float p_r, float p_g, float p_b)
: Color(p_r, p_g, p_b, 1.0f)
{
}
	
inline Color::Color(float p_r, float p_g, float p_b, float p_a)
: Color((uint8_t)(p_r * 255), (uint8_t)(p_g * 255), (uint8_t)(p_b * 255), (uint8_t)(p_a * 255))
{
}
	
inline Color Color::Darken(float percentage) const
{
	return Color(std::max(0, (int)(R - 255 * percentage)),
				 std::max(0, (int)(G - 255 * percentage)),
				 std::max(0, (int)(B - 255 * percentage)),
				 A);
}

inline Color Color::Lighten(float percentage) const
{
	return Color(std::min(255, (int)(R + 255 * percentage)),
				 std::min(255, (int)(G + 255 * percentage)),
				 std::min(255, (int)(B + 255 * percentage)),
				 A);
}

}