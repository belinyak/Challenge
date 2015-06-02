#include <Math\Vector3.h>

namespace Challenge
{

	Vector3::Vector3()
		: x(0)
		, y(0)
		, z(0)
	{}
	Vector3::Vector3(float xyz)
		: x(xyz)
		, y(xyz)
		, z(xyz)
	{}
	Vector3::Vector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{}
	Vector3::Vector3(float xyz[3])
		: x(xyz[0])
		, y(xyz[1])
		, z(xyz[2])
	{}
	Vector3::Vector3(const Vector2& other, float z)
		: x(other.x)
		, y(other.y)
		, z(z)
	{}


	bool Vector3::operator==(const Vector3& other) const
	{
		for (usize i = 0; i < 3; i++)
		{
			if (data[i] != other.data[i]) {
				return( false);
			}
		}
		return( true);
	}
	bool Vector3::operator!=(const Vector3& other) const{
		return( !operator==(other));
	}

	Vector3 Vector3::operator+(const Vector3& other) const{
		return( Vector3(x + other.x, y + other.y, z + other.z));
	}
	Vector3 Vector3::operator-(const Vector3& other) const{
		return(Vector3(x - other.x, y - other.y, z - other.z));
	}
	Vector3 Vector3::operator*(float scalar) const{
		return( Vector3(scalar * x, scalar * y, scalar * z));
	}
	Vector3 Vector3::operator/(float scalar) const{
		return( Vector3(x / scalar, y / scalar, z / scalar));
	}

	// Hadamard Product
	Vector3  Vector3::operator*(const Vector3& other) const
	{
		Vector3 result;
		for (usize i = 0; i < 3; i++) {
			result[i] = data[i] * other.data[i];
		}
		return( result);
	}
	Vector3& Vector3::operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return( *this);
	}
	Vector3& Vector3::operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return( *this);
	}
	Vector3& Vector3::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return(*this);
	}
	Vector3& Vector3::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return( *this );
	}

} // !namespace Challenge
