#pragma once

#include "Point.h"
#include "Size.h"

#include <algorithm>

namespace SDL {

class Rect
{
public:
	Rect() {}
	Rect(const Size &size);
	Rect(const Point &position, const Size &size);
	
	Rect operator +(const Point &pos) const;
	Rect operator -(const Point &pos) const;
	
	Rect Scale(double factor) const;
	Rect Scale(double factorWidth, double factorHeight) const;
	
	bool IsEmpty() const;
	Rect Intersect(const Rect &other) const;
	bool Contains(const Point &point) const;
	
	Point Position;
	Size Size;
	
	Point GetBottomRight() const;
	void SetBottomRight(const Point &bottomRight);
};
	
inline Rect::Rect(const class Size &p_size)
: Position(Point(0, 0)),
  Size(p_size)
{
	
}
	
inline Rect::Rect(const Point &p_position, const class Size &p_size)
: Position(p_position),
  Size(p_size)
{
}
	
inline Point Rect::GetBottomRight() const
{
	return Point(Position.X + Size.Width, Position.Y + Size.Height);
}
	
inline void Rect::SetBottomRight(const Point &p_bottomRight)
{
	Size.Width = p_bottomRight.X - Position.X;
	Size.Height = p_bottomRight.Y - Position.Y;
}


inline Rect Rect::operator +(const Point &p_offset) const
{
	return Rect(Position + p_offset, Size);
}
	
inline Rect Rect::operator -(const Point &p_offset) const
{
	return Rect(Position - p_offset, Size);
}
	
inline Rect Rect::Scale(double factor) const
{
	class Size newSize(int(Size.Width * factor), int(Size.Height * factor));
	
	return Rect(Position, newSize);
}

inline Rect Rect::Scale(double factorWidth, double factorHeight) const
{
	class Size newSize(int(Size.Width * factorWidth), int(Size.Height * factorHeight));
	
	return Rect(Position, newSize);
}

inline bool Rect::IsEmpty() const
{
	return Position.X == 0 && Position.Y == 0 && Size.Width == 0 && Size.Height == 0;
}
	
inline Rect Rect::Intersect(const Rect &other) const
{
	class Size size(0, 0);
	Rect rect(Point(0, 0), size);
	
	// Get the left and the right rects
	const Rect *leftRect, *rightRect;
	if (Position.X < other.Position.X) {
		leftRect = this;
		rightRect = &other;
	}
	else {
		leftRect = &other;
		rightRect = this;
	}
	
	if (leftRect->GetBottomRight().X > rightRect->Position.X) {

		// Get the top and bottom rects
		const Rect *topRect, *bottomRect;
		if (Position.Y < other.Position.Y) {
			topRect = this;
			bottomRect = &other;
		}
		else {
			topRect = &other;
			bottomRect = this;
		}
		
		if (topRect->GetBottomRight().Y > bottomRect->Position.Y) {
			rect.Position = Point(rightRect->Position.X, bottomRect->Position.Y);
			rect.SetBottomRight(Point(std::min(leftRect->GetBottomRight().X, rightRect->GetBottomRight().X), std::min(topRect->GetBottomRight().Y, bottomRect->GetBottomRight().Y)));
		}
	}
	
	return rect;
}

inline bool Rect::Contains(const Point &p_point) const
{
	return p_point.X >= Position.X && p_point.X < Position.X + Size.Width && p_point.Y >= Position.Y && p_point.Y < Position.Y + Size.Height;
}

	
}