#include <Math\Vector2.h>

namespace Challenge
{

//Note(mate): constructors
Vector2::Vector2()
	: x(0)
	, y(0)
{}

Vector2::Vector2(float _xy)
	: x(_xy)
	, y(_xy)
{}

Vector2::Vector2(float _x, float _y)
	: x(_x)
	, y(_y)
{}

Vector2::Vector2(float _xy[2])
	: x(_xy[0])
	, y(_xy[1])
{}

//Note(mate): operators

Vector2 Vector2::operator+(const Vector2& _other) const
{
	return Vector2(x + _other.x, y + _other.y);
}

Vector2 Vector2::operator-(const Vector2& _other) const
{
	return Vector2(x - _other.x, y - _other.y);

}

Vector2 Vector2::operator*(float _scalar) const
{
	return Vector2(x * _scalar, y * _scalar);

}

Vector2 Vector2::operator/(float _scalar) const
{
	return Vector2(x / _scalar, y / _scalar);
}

Vector2& Vector2::operator+=(const Vector2& _other)
{
	x += _other.x;
	y += _other.y;

	return(*this);
}

Vector2& Vector2::operator-=(const Vector2& _other)
{
	x -= _other.x;
	y -= _other.y;

	return(*this);
}

Vector2& Vector2::operator*=(float _scalar)
{
	x *= _scalar;
	y *= _scalar;

	return(*this);
}

Vector2& Vector2::operator/=(float _scalar)
{
	x /= _scalar;
	y /= _scalar;

	return(*this);
}

} //namespace Challenge