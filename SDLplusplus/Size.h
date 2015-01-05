#pragma once

#include "Point.h"

namespace SDL {

class Size
{
public:
	Size() {}
	Size(int width, int Height);
	
	Point Center() const;
	
	int Width;
	int Height;
};

inline Size::Size(int p_width, int p_height)
{
	Width = p_width;
	Height = p_height;
}

inline Point Size::Center() const
{
	return Point(Width / 2, Height / 2);
}

}