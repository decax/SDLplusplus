#pragma once

namespace SDL {
	
class Point
{
public:
	Point() {}
	Point(int x, int y);
	
	Point operator +(const Point &offset) const;
	Point operator -(const Point &offset) const;
	
	int X;
	int Y;
};

inline Point::Point(int p_x, int p_y)
{
	X = p_x;
	Y = p_y;
}

inline Point Point::operator +(const Point &offset) const
{
	return Point(X + offset.X, Y + offset.Y);
}

inline Point Point::operator -(const Point &offset) const
{
	return Point(X - offset.X, Y - offset.Y);
}

}