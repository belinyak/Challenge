#ifndef CHALLENGE_VECTOR2_H
#define CHALLENGE_VECTOR2_H

#include <Source\Types.hpp>
#include <cmath>
#include <iostream>

namespace Challenge
{
struct Vector2
{
	Vector2();
	explicit Vector2(float _xy);
	Vector2(float _x, float _y);
	Vector2(float _xy[2]);

	float& operator[](usize _index) { 
		return( data[_index]);
	};
	const float& operator[](usize _index) const {
		return( data[_index] ); 
	};

	Vector2(const Vector2& _other) = default;

	Vector2 operator+(const Vector2& _other) const;
	Vector2 operator-(const Vector2& _other) const;
	Vector2 operator*(float _scalar) const;
	Vector2 operator/(float _scalar) const;

	Vector2& operator+=(const Vector2& _other);
	Vector2& operator-=(const Vector2& _other);
	Vector2& operator*=(float _scalar);
	Vector2& operator/=(float _scalar);

	bool operator==(const Vector2& _other) const;
	bool operator!=(const Vector2& _other) const;

	Vector2 operator*(const Vector2& _other) const;

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
	return( _vector * _scalar ); 
}

//Note(mate): skaláris szorzat 
inline float
dot(const Vector2& _a, const Vector2& _b)
{
	return( _a.x * _b.x + _a.y * _b.y );
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
	return( dot(_a, _a) );
}

//Note(mate): vektor hossza
inline float
length(const Vector2& _a)
{
	return( std::sqrtf(lengthSquared(_a)));
}

//Note(mate): normalizált v/hossz(v)
inline Vector2
normalized(const Vector2& _a)
{
	return( _a  * (1.0f / length(_a)));
}

//Note(mate): teszteléshez
inline std::ostream& operator<<(std::ostream& _os, const Vector2& _v)
{
	return( _os << "Vector2( "  << _v[0] << " " << _v[1] << " )");
}

} //namespace Challenge
#endif // !#define CHALLENGE_VECTOR2_H

