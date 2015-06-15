#ifndef CHALLENGE_QUATERNION_HPP
#define CHALLENGE_QUATERNION_HPP

#include <Math/Vector3.hpp>
#include <Math/Matrix4.hpp>
#include <Math/Angle.hpp>
#include <Math/Constants.hpp>

namespace Challenge
{
struct Quaternion
{

	Quaternion()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{}

	Quaternion(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w)
	{}

	Quaternion(const Vector3& _v, float _s)
		: x(_v.x)
		, y(_v.y)
		, z(_v.z)
		, w(_s)
	{}

	inline const float operator[](usize _index) const {
		return(data[_index]);
	}
	inline float& operator[](usize _index) {
		return(data[_index]);
	}

	Quaternion operator-() const
	{
		Quaternion value;
		value.x = -x;
		value.y = -y;
		value.z = -z;
		value.w = -w;
		return(value);
	}

	Quaternion operator+(const Quaternion& _other) const
	{
		Quaternion value;
		value.x = x + _other.x;
		value.y = y + _other.y;
		value.z = z + _other.z;
		value.w = w + _other.w;
		return(value);
	}
	Quaternion operator-(const Quaternion& _other) const
	{
		Quaternion value;
		value.x = x - _other.x;
		value.y = y - _other.y;
		value.z = z - _other.z;
		value.w = w - _other.w;
		return(value);
	}
	Quaternion operator*(const Quaternion& _other) const
	{
		Quaternion value;

		value.x = this->w * _other.x + this->x * _other.w + this->y * _other.z - this->z * _other.y;
		value.y = this->w * _other.y - this->x * _other.z + this->y * _other.w + this->z * _other.x;
		value.z = this->w * _other.z + this->x * _other.y - this->y * _other.x + this->z * _other.w;
		value.w = this->w * _other.w - this->x * _other.x - this->y * _other.y - this->z * _other.z;

		return(value);
	}

	Quaternion operator*(float _s) const
	{
		Quaternion value = *this;

		value.x *= _s;
		value.y *= _s;
		value.z *= _s;
		value.w *= _s;

		return(value);
	}
	Quaternion operator/(float _s) const
	{
		Quaternion value = *this;

		value.x /= _s;
		value.y /= _s;
		value.z /= _s;
		value.w /= _s;

		return(value);
	}

	bool operator==(const Quaternion& _other) const
	{
		for (int i = 0; i < 4; i++) {
			if (data[i] != _other.data[i]) {
				return(false);
			}
		}
		return(true);
	}

	//TODO(mate): tutijo-é??
	bool operator!=(const Quaternion& _other) const
	{
		return(!(this->data == _other.data));
	}

	Vector3 vector() const
	{
		return((const Vector3&)(data));
	}
	Vector3& vector()
	{
		return((Vector3&)(data));

	}

	float scalar() const
	{
		return(w);
	}
	float& scalar()
	{
		return(w);
	}

	float lengthSquared() const
	{
		return(x*x + y*y + z*z + w*w);
	}
	float length() const
	{
		return(std::sqrt(lengthSquared()));
	}

	union
	{
		float data[4];
		struct
		{
			float x, y, z, w;
		};
	};

};

inline Quaternion operator*(float _s, const Quaternion& _other)
{
	return(_s * _other);
}
inline float dot(const Quaternion& _q1, const Quaternion& _q2)
{
	return(dot(_q1.vector(), _q2.vector() + _q1.w * _q2.w));
}
inline Quaternion cross(const Quaternion& _q1, const Quaternion& _q2)
{
	return (Quaternion(_q1.w * _q2.x + _q1.x * _q2.w + _q1.y * _q2.z - _q1.z * _q2.y,
			  _q1.w * _q2.y + _q1.y * _q2.w + _q1.z * _q2.x - _q1.x * _q2.z,
			  _q1.w * _q2.z + _q1.z * _q2.w + _q1.x * _q2.y - _q1.y * _q2.x,
			  _q1.w * _q2.w - _q1.x * _q2.x - _q1.y * _q2.y - _q1.z * _q2.z));
}

inline Quaternion normalize(const Quaternion& _q)
{
	return(_q * (1.0f / _q.length()));
}
inline Quaternion conjugate(const Quaternion& _q)
{
	Quaternion value(-_q.vector(), _q.w);
	return(value);
}
inline Quaternion inverse(const Quaternion& _q)
{
	Quaternion value = conjugate(_q) / dot(_q, _q);
}

inline Vector3 operator*(const Quaternion& _q, const Vector3& _v)
{
	Vector3 value = 2.0f * cross(_q.vector(), _v);
	return (_v + _q.w * value + cross(_q.vector(), value));

}

inline Radian angle(const Quaternion& _q)
{
	return Radian(2.0f * std::acos(_q.w));
}
inline Vector3 axis(const Quaternion& _q)
{
	float s2 = 1.0f - _q.w * _q.w;

	if (s2 <= 0.0f) {
		return Vector3(0, 0, 1);
	}

	f32 invs2 = 1.0f / std::sqrt(s2);

	return _q.vector() * invs2;
}
inline Quaternion angleAxis(const Radian& _angle, const Vector3& _axis)
{
	Quaternion value;

	const Vector3 a = normalize(_axis);

	const float s = std::sin((float)(0.5f * _angle));

	value.vector() = a * s;
	value.w = std::cos((float)(0.5f * _angle));


	return(value);
}

struct EulerAngles
{
	Radian pitch;
	Radian yaw;
	Radian roll;
};

inline Radian roll(const Quaternion& _q)
{
	return Radian(
		std::atan2(2.0f * _q[0] * _q[1] + _q[2] * _q[3],
		_q[0] * _q[0] + _q[3] * _q[3] - _q[1] * _q[1] - _q[2] * _q[2]));
}
inline Radian pitch(const Quaternion& _q)
{
	return Radian(
		std::atan2(2.0f * _q[1] * _q[2] + _q[3] * _q[0],
		_q[3] * _q[3] - _q[0] * _q[0] - _q[1] * _q[1] + _q[2] * _q[2]));
}
inline Radian yaw(const Quaternion& _q)
{
	return Radian(std::asin(-2.0f * (_q[0] * _q[2] - _q[3] * _q[1])));
}

inline EulerAngles quaternionToEulerAngles(const Quaternion& _q)
{
	return{ pitch(_q), yaw(_q), roll(_q) };
}

inline Matrix4 quaternionToMatrix4(const Quaternion& _q)
{
	Matrix4 mat(1);
	Quaternion a = normalize(_q);

	const f32 xx = a.x * a.x;
	const f32 yy = a.y * a.y;
	const f32 zz = a.z * a.z;
	const f32 xy = a.x * a.y;
	const f32 xz = a.x * a.z;
	const f32 yz = a.y * a.z;
	const f32 wx = a.w * a.x;
	const f32 wy = a.w * a.y;
	const f32 wz = a.w * a.z;

	mat[0][0] = 1.0f - 2.0f * (yy + zz);
	mat[0][1] = 2.0f * (xy + wz);
	mat[0][2] = 2.0f * (xz - wy);

	mat[1][0] = 2.0f * (xy - wz);
	mat[1][1] = 1.0f - 2.0f * (xx + zz);
	mat[1][2] = 2.0f * (yz + wx);

	mat[2][0] = 2.0f * (xz + wy);
	mat[2][1] = 2.0f * (yz - wx);
	mat[2][2] = 1.0f - 2.0f * (xx + yy);

	return(mat);
}

inline Quaternion matrix4ToQuaternion(const Matrix4& m)
{
	f32 fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
	f32 fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
	f32 fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
	f32 fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

	int biggestIndex = 0;
	f32 fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	f32 biggestVal = std::sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
	f32 mult = 0.25f / biggestVal;

	Quaternion q;

	switch (biggestIndex)
	{
	case 0:
	{
		q.w = biggestVal;
		q.x = (m[1][2] - m[2][1]) * mult;
		q.y = (m[2][0] - m[0][2]) * mult;
		q.z = (m[0][1] - m[1][0]) * mult;
	}
	break;
	case 1:
	{
		q.w = (m[1][2] - m[2][1]) * mult;
		q.x = biggestVal;
		q.y = (m[0][1] + m[1][0]) * mult;
		q.z = (m[2][0] + m[0][2]) * mult;
	}
	break;
	case 2:
	{
		q.w = (m[2][0] - m[0][2]) * mult;
		q.x = (m[0][1] + m[1][0]) * mult;
		q.y = biggestVal;
		q.z = (m[1][2] + m[2][1]) * mult;
	}
	break;
	case 3:
	{
		q.w = (m[0][1] - m[1][0]) * mult;
		q.x = (m[2][0] + m[0][2]) * mult;
		q.y = (m[1][2] + m[2][1]) * mult;
		q.z = biggestVal;
	}
	break;
	default: // Should never actually get here. Just for sanities sake.
	{
		//assert(false);
	}
	break;
	}

	return q;
}

} //!namespace Challenge
#endif // !#define CHALLENGE_QUATERNION_HPP

