#include <Math\Vector2.h>

namespace Challenge
{

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

Vector2 Vector2::operator+(const Vector2& _other) const
{
	return( Vector2(x + _other.x, y + _other.y));
}

Vector2 Vector2::operator-(const Vector2& _other) const
{
	return( Vector2(x - _other.x, y - _other.y) );

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

Vector2 Vector2::operator*(const Vector2& other) const
{
	Vector2 result;
	for (usize i = 0; i < 2; i++)
		result[i] = data[i] * other.data[i];
	return( result );
}

bool Vector2::operator==(const Vector2& _other) const
{
	if ( data[0] != _other[0] || 
		data[1] != _other [1])
	{
		return(false);
	}
	return(true);
}

bool Vector2::operator!=(const Vector2& _other) const 
{
	if (data[0] == _other[0] ||
		data[1] == _other[1])
	{
		return(false);
	}
	return(true);
}

Vector2 Vector2::operator*(float _scalar) const
{
	return( Vector2(x * _scalar, y * _scalar) );

}

Vector2 Vector2::operator/(float _scalar) const
{
	return( Vector2(x / _scalar, y / _scalar) );
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