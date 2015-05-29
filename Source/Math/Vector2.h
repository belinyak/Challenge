#ifndef CHALLENGE_VECTOR2_H
#define CHALLENGE_VECTOR2_H

#include <Source\Types.hpp>
#include <cmath>

namespace Challenge
{

struct Vector2
{
	//Note(mate): constructors
	Vector2();
	explicit Vector2(float _xy);
	Vector2(float _x, float _y);
	Vector2(float _xy[2]);

	//Note(mate): operators
	float& operator[](usize _index) { return data[_index]; };
	const float& operator[](usize _index) const { return data[_index]; };

	Vector2 operator+(const Vector2& _other) const;
	Vector2 operator-(const Vector2& _other) const;
	Vector2 operator*(float _scalar) const;
	Vector2 operator/(float _scalar) const;
	Vector2& operator+=(const Vector2& _other);
	Vector2& operator-=(const Vector2& _other);
	Vector2& operator*=(float _scalar);
	Vector2& operator/=(float _scalar);

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
inline Vector2
operator*(float _scalar, const Vector2& _vector) { return _vector * _scalar; }

//Note(mate): 
inline float
dot(const Vector2& _a, const Vector2& _b)
{
	return _a.x * _b.x + _a.y * _b.y;
}

//Note(mate): 
inline float
cross(const Vector2& _a, const Vector2& _b)
{
	return _a.x * _b.y - _b.x * _a.y;
}

//Note(mate): 
inline float
lengthSquared(const Vector2& _a)
{
	return dot(_a, _a);
}

//Note(mate): 
inline float
length(const Vector2& _a)
{
	return std::sqrtf(lengthSquared(_a));
}

//Note(mate): 
inline Vector2
normalized(const Vector2& _a)
{
	return _a  * (1.0f / length(_a));
}

} //namespace Challenge

#endif // !#define CHALLENGE_VECTOR2_H

