#ifndef CHALLENGE_MATH_VECTOR4_H
#define CHALLENGE_MATH_VECTOR4_H

#include <cmath>

#include <Math/Vector3.h>
#include <Math/Vector2.h>

struct Vector4
{
	Vector4();
	explicit Vector4(float xyzw);
	Vector4(float x, float y, float z, float w);
	Vector4(float xyzw[4]);
	Vector4(const Vector4& _other) = default;

	explicit Vector4(const Vector2& xy, float z, float w);
	explicit Vector4(const Vector2& xy, const Vector2& zw);
	explicit Vector4(const Vector3& xyz, float w);

	Vector4 operator-() const;

	float& operator[](std::size_t index) { return( data[index]); }
	const float& operator[](std::size_t index) const { return( data[index]); }

	bool operator==(const Vector4& other) const;

	bool operator!=(const Vector4& other) const;

	Vector4 operator+(const Vector4& other) const;
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator*(float scalar) const;

	// Hadamard Product
	inline Vector4 operator*(const Vector4& other) const
	{
		Vector4 result;
		for (std::size_t i = 0; i < 4; i++) {
			result[i] = data[i] * other.data[i];
		}
		return( result);
	}
	inline Vector4 operator/(const Vector4& _other) const
	{
		Vector4 result;
		for (std::size_t i = 0; i < 4; i++) {
			result[i] = data[i] / _other.data[i];
		}
		return(result);
	}

	inline Vector4 operator/(float scalar) const
	{
		return(( Vector4(x / scalar, y / scalar, z / scalar, w / scalar) ));
	}
	inline Vector4& operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return(*this);
	}
	inline Vector4& operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return( *this);
	}
	inline Vector4& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return( *this);
	}
	inline Vector4& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;

		return(*this);
	}

	union
	{
		float data[4];
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
		struct
		{
			float s, t, p, q;
		};
	};
};

inline Vector4 operator*(float scalar, const Vector4& vector){
	return( vector * scalar);
}

inline float dot(const Vector4& a, const Vector4& b)
{
	return( a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

inline float lengthSquared(const Vector4& a) { 
	return( dot(a, a)); 
}

inline float length(const Vector4& a) { 
	return( sqrtf(lengthSquared(a))); 
}

inline Vector4 normalize(const Vector4& a) {
	return( a * (1.0f / length(a)));
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& v){
	return( os << "Vector4(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")");
}

#endif