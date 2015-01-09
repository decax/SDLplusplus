#pragma once

namespace SDL {
	
class Point
{
public:
	Point() {}
	Point(int x, int y);
	
	bool operator ==(const Point &other) const;
	bool operator !=(const Point &other) const;
	
	Point operator +(const Point &offset) const;
	Point operator -(const Point &offset) const;

	Point operator +=(const Point &offset);
	Point operator -=(const Point &offset);
	
	int X;
	int Y;
};

inline Point::Point(int p_x, int p_y)
{
	X = p_x;
	Y = p_y;
}

inline bool Point::operator ==(const Point &other) const
{
	return X == other.X && Y == other.Y;
}

inline bool Point::operator !=(const Point &other) const
{
	return X != other.X || Y != other.Y;
}
	
inline Point Point::operator +(const Point &offset) const
{
	return Point(X + offset.X, Y + offset.Y);
}

inline Point Point::operator -(const Point &offset) const
{
	return Point(X - offset.X, Y - offset.Y);
}

inline Point Point::operator +=(const Point &offset)
{
	X += offset.X;
	Y += offset.Y;
	
	return *this;
}

inline Point Point::operator -=(const Point &offset)
{
	X -= offset.X;
	Y -= offset.Y;
	
	return *this;
}

	
}