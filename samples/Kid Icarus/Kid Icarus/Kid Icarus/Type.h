#pragma once

enum Direction
{
	UP, DOWN, LEFT, RIGHT
};

class Vector2
{
public:
	float x, y;
	
	Vector2() {}
	Vector2(float x, float y);
	
	Vector2 operator +=(const Vector2 &other);
	Vector2 operator *=(const Vector2 &other);

	Vector2 operator *(const Vector2 &other) const;
	Vector2 operator *(float factor) const;
};

inline Vector2::Vector2(float p_x, float p_y)
{
	x = p_x;
	y = p_y;
}

inline Vector2 Vector2::operator +=(const Vector2 &p_other)
{
	x += p_other.x;
	y += p_other.y;
	
	return *this;
}

inline Vector2 Vector2::operator *=(const Vector2 &p_other)
{
	x *= p_other.x;
	y *= p_other.y;
	
	return *this;
}

inline Vector2 Vector2::operator *(const Vector2 &p_other) const
{
	return Vector2(x * p_other.x, y * p_other.y);
}

inline Vector2 Vector2::operator *(float p_factor) const
{
	return Vector2(x * p_factor, y * p_factor);
}
