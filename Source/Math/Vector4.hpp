#ifndef CHALLENGE_MATH_VECTOR4_HPP
#define CHALLENGE_MATH_VECTOR4_HPP

#include <Source/Types.hpp>
#include <cmath>

#include <Math/Vector3.hpp>
#include <Math/Vector2.hpp>

namespace Challenge
{
struct Vector4
{
	Vector4()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{}

	explicit Vector4(float xyzw)
		: x(xyzw)
		, y(xyzw)
		, z(xyzw)
		, w(xyzw)
	{}

	Vector4(float x, float y, float z, float w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{}

	Vector4(float xyzw[4])
		: x(xyzw[0])
		, y(xyzw[1])
		, z(xyzw[2])
		, w(xyzw[3])
	{}

	Vector4(const Vector4& _other) = default;

	explicit Vector4(const Vector2& xy, float z, float w)
		: x(xy.x)
		, y(xy.y)
		, z(z)
		, w(w)
	{}

	explicit Vector4(const Vector2& xy, const Vector2& zw)
		: x(xy.x)
		, y(xy.y)
		, z(zw.x)
		, w(zw.y)
	{}

	explicit Vector4(const Vector3& xyz, float w)
		: x(xyz.x)
		, y(xyz.y)
		, z(xyz.z)
		, w(w)
	{}

	float& operator[](usize index) { return( data[index]); }
	const float& operator[](usize index) const { return( data[index]); }

	bool operator==(const Vector4& other) const
	{
		for (usize i = 0; i < 4; i++)
		{
			if (data[i] != other.data[i]) {
				return( false);
			}
		}
		return( true);
	}

	bool operator!=(const Vector4& other) const	{
		return( (!operator==(other)));
	}

	Vector4 operator+(const Vector4& other) const{
		return( (Vector4(x + other.x, y + other.y, z + other.z, w + other.w)));
	}

	Vector4 operator-(const Vector4& other) const	{
		return(( Vector4(x - other.x, y - other.y, z - other.z, w - other.w) ));
	}

	Vector4 operator*(float scalar) const	{
		return( (Vector4(scalar * x, scalar * y, scalar * z, scalar * w)));
	}

	// Hadamard Product
	Vector4 operator*(const Vector4& other) const
	{
		Vector4 result;
		for (usize i = 0; i < 4; i++) {
			result[i] = data[i] * other.data[i];
		}
		return( result);
	}

	Vector4 operator/(float scalar) const
	{
		return(( Vector4(x / scalar, y / scalar, z / scalar, w / scalar) ));
	}

	Vector4& operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return(*this);
	}

	Vector4& operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return( *this);
	}

	Vector4& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;

		return( *this);
	}

	Vector4& operator/=(float scalar)
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
	return( std::sqrtf(lengthSquared(a))); 
}

inline Vector4 normalize(const Vector4& a) {
	return( a * (1.0f / length(a)));
}

inline std::ostream& operator<<(std::ostream& os, const Vector4& v){
	return( os << "Vector4(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")");
}

} // !namespace Dunjun
#endif