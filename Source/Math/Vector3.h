#ifndef CHALLENGE_MATH_VECTOR3_H
#define CHALLENGE_MATH_VECTOR3_H

#include <Source\Types.hpp>
#include <Math\Vector2.h>

#include <iostream>

namespace Challenge
{

struct Vector3
{
	Vector3();
	Vector3(float xyz);
	Vector3(float x, float y, float z);
	Vector3(float xyz[3]);
	Vector3(const Vector2& other, float z);

	Vector3(const Vector3& _other) = default;

	Vector3 operator-() const {
		return{ -x,-y,-z };
	}

	float& operator[](usize _index);
	const float& operator[](usize _index) const;
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(float scalar) const;
	Vector3 operator/(float scalar) const;

	// Hadamard Product
	inline Vector3  operator*(const Vector3& other) const
	{
		Vector3 result;
		for (usize i = 0; i < 3; i++) {
			result[i] = data[i] * other.data[i];
		}
		return(result);
	}
	inline Vector3 operator/(const Vector3& _other) const
	{
		Vector3 result;
		for (usize i = 0; i < 3; i++) {
			result[i] = data[i] / _other.data[i];
		}
		return(result);
	}
	inline Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return(*this);
	}
	inline Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return(*this);
	}
	inline Vector3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return(*this);
	}
	inline Vector3& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return(*this);
	}

	union
	{
		float data[3];
		struct
		{
			float x, y, z;
		};
		struct
		{
			float r, g, b;
		};
		struct
		{
			float s, t, p;
		};
	};
};

inline Vector3 operator*(float _scalar, const Vector3& _vector) {
	return(_vector * _scalar);
}

inline float dot(const Vector3& _a, const Vector3& _b) {
	return(_a.x * _b.x + _a.y * _b.y + _a.z * _b.z);
}

inline Vector3 cross(const Vector3& _a, const Vector3& _b)
{
	return(Vector3(_a.y * _b.z - _b.y * _a.z, // x
		   _a.z * _b.x - _b.z * _a.x, // y
		   _a.x * _b.y - _b.x * _a.y  // z
		   ));
}

inline float lengthSquared(const Vector3& a) {
	return(dot(a, a));
}
inline float length(const Vector3& a) {
	return(std::sqrtf(lengthSquared(a)));
}

inline Vector3 normalize(const Vector3& a) {
	return(a * (1.0f / length(a)));
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
	return(os << "Vector3(" << v[0] << ", " << v[1] << ", " << v[2] << ")");
}
} //namespace Challenge
#endif // !#define CHALLENGE_VECTOR3_H
