#pragma once

namespace SDL {

class Size
{
public:
	Size() {}
	Size(int width, int Height);
	
	bool operator ==(const Size &other) const;
	bool operator !=(const Size &other) const;
	
	Size operator /(int factor) const;
	
	int Width;
	int Height;
};

inline Size::Size(int p_width, int p_height)
{
	Width = p_width;
	Height = p_height;
}

inline bool Size::operator ==(const Size &p_other) const
{
	return Width == p_other.Width && Height == p_other.Height;
}

inline bool Size::operator !=(const Size &p_other) const
{
	return Width != p_other.Width || Height != p_other.Height;
}
	
inline Size Size::operator /(int p_factor) const
{
	return Size(Width / p_factor, Height / p_factor);
}


}