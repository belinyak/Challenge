#ifndef CHALLENGE_VECTOR3_H
#define CHALLENGE_VECTOR3_H

#include <Source\Types.hpp>
#include <Math\Vector2.h>

#include <iostream>

namespace Challenge
{

struct Vector3
{
	Vector3();
	explicit Vector3(float _xyz);
	Vector3(float _x, float _y, float _z);
	Vector3(float _xyz[3]);

	explicit Vector3(const Vector2& _other, float _z);
	Vector3(const Vector3& _other) = default;


	float& operator[](usize _index) { 
		return( data[_index]);
	}
	const float& operator[](usize _index) const {
		return( data[_index]);
	}

	bool operator==(const Vector3& _other) const;
	bool operator!=(const Vector3& _other) const;

	Vector3 operator+(const Vector3& _other) const;
	Vector3 operator-(const Vector3& _other) const;
	Vector3 operator*(float _scalar) const;
	Vector3 operator/(float _scalar) const;

	// Hadamard Product
	Vector3 operator*(const Vector3& _other) const;
	Vector3& operator+=(const Vector3& _other);
	Vector3& operator-=(const Vector3& _other);
	Vector3& operator*=(float _scalar);
	Vector3& operator/=(float _scalar);

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


inline Vector3 operator*(float _scalar, const Vector3& _vector){
	return( _vector * _scalar);
}

inline float dot(const Vector3& _a, const Vector3& _b){
	return( _a.x * _b.x + _a.y * _b.y + _a.z * _b.z);
}

inline Vector3 cross(const Vector3& _a, const Vector3& _b)
{
	return( Vector3(_a.y * _b.z - _b.y * _a.z, // x
					_a.z * _b.x - _b.z * _a.x, // y
					_a.x * _b.y - _b.x * _a.y  // z
				   ));
}

inline float lengthSquared(const Vector3& a) { 
	return( dot(a, a));
}

inline float length(const Vector3& a) { 
	return( std::sqrtf(lengthSquared(a))); 
}

inline Vector3 normalized(const Vector3& a) {
	return( a * (1.0f / length(a))); 
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v){
	return( os << "Vector3(" << v[0] << ", " << v[1] << ", " << v[2] << ")");
}


} //namespace Challenge
#endif // !#define CHALLENGE_VECTOR3_H
