#pragma once

#include "Size.h"

namespace SDL {
	
class Point
{
public:
	Point() {}
	Point(int x, int y);
	Point(Size size);
	
	bool operator ==(const Point &other) const;
	bool operator !=(const Point &other) const;
	
	Point operator +(const Point &offset) const;
	Point operator -(const Point &offset) const;

	Point operator +=(const Point &offset);
	Point operator -=(const Point &offset);
	
	Point operator +(const Size &offset) const;
	Point operator -(const Size &offset) const;
	
	Point operator +=(const Size &offset);
	Point operator -=(const Size &offset);

	int X;
	int Y;
};

inline Point::Point(int p_x, int p_y)
{
	X = p_x;
	Y = p_y;
}
	
inline Point::Point(Size p_size)
{
	X = p_size.Width;
	Y = p_size.Height;
}

inline bool Point::operator ==(const Point &p_offset) const
{
	return X == p_offset.X && Y == p_offset.Y;
}

inline bool Point::operator !=(const Point &p_offset) const
{
	return X != p_offset.X || Y != p_offset.Y;
}
	
inline Point Point::operator +(const Point &p_offset) const
{
	return Point(X + p_offset.X, Y + p_offset.Y);
}

inline Point Point::operator -(const Point &p_offset) const
{
	return Point(X - p_offset.X, Y - p_offset.Y);
}

inline Point Point::operator +=(const Point &p_offset)
{
	X += p_offset.X;
	Y += p_offset.Y;
	
	return *this;
}

inline Point Point::operator -=(const Point &offset)
{
	X -= offset.X;
	Y -= offset.Y;
	
	return *this;
}
	
inline Point Point::operator +(const Size &p_offset) const
{
	return Point(X + p_offset.Width, Y + p_offset.Height);
}

inline Point Point::operator -(const Size &p_offset) const
{
	return Point(X - p_offset.Width, Y - p_offset.Height);
}

inline Point Point::operator +=(const Size &p_offset)
{
	X += p_offset.Width;
	Y += p_offset.Height;
	
	return *this;
}

inline Point Point::operator -=(const Size &p_offset)
{
	X -= p_offset.Width;
	Y -= p_offset.Height;
	
	return *this;
}

	
}