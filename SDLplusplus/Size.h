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
	
	void ScaleProportionalWidth(int width);
	void ScaleProportionalHeight(int height);
	
	Size GetScaledProportionalWidth(int width) const;
	Size GetScaledProportionalHeight(int height) const;

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
	
inline void Size::ScaleProportionalWidth(int p_width)
{
	Height = (int)(Height * ((float)p_width / Width));
	Width = p_width;
}

inline void Size::ScaleProportionalHeight(int p_height)
{
	Width = (int)(Width * ((float)p_height) / Height);
	Height = p_height;
}

inline Size Size::GetScaledProportionalWidth(int p_width) const
{
	return Size(p_width, (int)(Height * ((float)p_width / Width)));
}

inline Size Size::GetScaledProportionalHeight(int p_height) const
{
	return Size((int)(Width * ((float)p_height / Height)), p_height);
}

}