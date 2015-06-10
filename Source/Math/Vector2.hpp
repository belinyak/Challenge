#ifndef CHALLENGE_VECTOR2_Hpp
#define CHALLENGE_VECTOR2_Hpp

#include <Source\Types.hpp>
#include <cmath>
#include <iostream>

namespace Challenge
{
struct Vector2
{
	Vector2()
		: x(0)
		, y(0)
	{}

	explicit Vector2(float _xy)
	: x(_xy)
		, y(_xy)
	{}
	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}
	Vector2(float _xy[2])
		: x(_xy[0])
		, y(_xy[1])
	{}

	inline float& operator[](usize _index) {
		return(data[_index]);
	};
	inline const float& operator[](usize _index) const {
		return(data[_index]);
	};

	Vector2(const Vector2& _other) = default;

	inline Vector2 operator-() const {
		return{ -x,-y };
	}

	inline Vector2 operator+(const Vector2& _other) const
	{
		return(Vector2(x + _other.x, y + _other.y));
	}
	inline Vector2 operator-(const Vector2& _other) const
	{
		return(Vector2(x - _other.x, y - _other.y));

	}
	inline Vector2 operator*(float _scalar) const
	{
		return(Vector2(x * _scalar, y * _scalar));

	}
	inline Vector2 operator/(float _scalar) const
	{
		return(Vector2(x / _scalar, y / _scalar));
	}

	inline Vector2& operator+=(const Vector2& _other)
	{
		x += _other.x;
		y += _other.y;

		return(*this);
	}
	inline Vector2& operator-=(const Vector2& _other)
	{
		x -= _other.x;
		y -= _other.y;

		return(*this);
	}
	inline Vector2& operator*=(float _scalar)
	{
		x *= _scalar;
		y *= _scalar;

		return(*this);
	}
	inline Vector2& operator/=(float _scalar)
	{
		x /= _scalar;
		y /= _scalar;

		return(*this);
	}

	inline Vector2 operator*(const Vector2& other) const
	{
		Vector2 result;
		for (usize i = 0; i < 2; i++)
			result[i] = data[i] * other.data[i];
		return(result);
	}

	inline bool operator==(const Vector2& _other) const
	{
		if (data[0] != _other[0] ||
			data[1] != _other[1])
		{
			return(false);
		}
		return(true);
	}
	inline bool operator!=(const Vector2& _other) const
	{
		if (data[0] == _other[0] ||
			data[1] == _other[1])
		{
			return(false);
		}
		return(true);
	}

	union
	{
		float data[2];
		struct
		{
			float x, y;
		};
		struct
		{
			float r, g;
		};
		struct
		{
			float s, t;
		};
	};
};

//Note(mate): calculations

//Note(mate): vektor * skalár
inline Vector2
operator*(float _scalar, const Vector2& _vector) {
	return(_vector * _scalar);
}

//Note(mate): skaláris szorzat 
inline float
dot(const Vector2& _a, const Vector2& _b)
{
	return(_a.x * _b.x + _a.y * _b.y);
}

/*
//TODO(mate): ezmiez?
inline float
cross(const Vector2& _a, const Vector2& _b)
{
return( _a.x * _b.y - _b.x * _a.y;
}
*/

//Note(mate): ez mire jó??
inline float
lengthSquared(const Vector2& _a)
{
	return(dot(_a, _a));
}

//Note(mate): vektor hossza
inline float
length(const Vector2& _a)
{
	return(std::sqrtf(lengthSquared(_a)));
}

//Note(mate): normalizált v/hossz(v)
inline Vector2
normalize(const Vector2& _a)
{
	return(_a  * (1.0f / length(_a)));
}

//Note(mate): teszteléshez
inline std::ostream& operator<<(std::ostream& _os, const Vector2& _v)
{
	return(_os << "Vector2( " << _v[0] << " " << _v[1] << " )");
}

} //namespace Challenge
#endif // !#define CHALLENGE_VECTOR2_HPP

