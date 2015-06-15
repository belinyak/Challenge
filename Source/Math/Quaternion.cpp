#include <Math\Quaternion.h>

namespace Challenge
{

Quaternion::Quaternion()
	: x(0)
	, y(0)
	, z(0)
	, w(0)
{}
Quaternion::Quaternion(float _x, float _y, float _z, float _w)
	: x(_x)
	, y(_y)
	, z(_z)
	, w(_w)
{}
Quaternion::Quaternion(const Vector3& _v, float _s)
	: x(_v.x)
	, y(_v.y)
	, z(_v.z)
	, w(_s)
{}

Quaternion Quaternion::operator-() const
{
	Quaternion value;
	value.x = -x;
	value.y = -y;
	value.z = -z;
	value.w = -w;
	return(value);
}
Quaternion Quaternion::operator+(const Quaternion& _other) const
{
	Quaternion value;
	value.x = x + _other.x;
	value.y = y + _other.y;
	value.z = z + _other.z;
	value.w = w + _other.w;
	return(value);
}
Quaternion Quaternion::operator-(const Quaternion& _other) const
{
	Quaternion value;
	value.x = x - _other.x;
	value.y = y - _other.y;
	value.z = z - _other.z;
	value.w = w - _other.w;
	return(value);
}
Quaternion Quaternion::operator*(const Quaternion& _other) const
{
	Quaternion value;

	value.x = this->w * _other.x + this->x * _other.w + this->y * _other.z - this->z * _other.y;
	value.y = this->w * _other.y - this->x * _other.z + this->y * _other.w + this->z * _other.x;
	value.z = this->w * _other.z + this->x * _other.y - this->y * _other.x + this->z * _other.w;
	value.w = this->w * _other.w - this->x * _other.x - this->y * _other.y - this->z * _other.z;

	return(value);
}
Quaternion Quaternion::operator*(float _s) const
{
	Quaternion value = *this;

	value.x *= _s;
	value.y *= _s;
	value.z *= _s;
	value.w *= _s;

	return(value);
}
Quaternion Quaternion::operator/(float _s) const
{
	Quaternion value = *this;

	value.x /= _s;
	value.y /= _s;
	value.z /= _s;
	value.w /= _s;

	return(value);
}

bool Quaternion::operator==(const Quaternion& _other) const
{
	for (int i = 0; i < 4; i++) {
		if (data[i] != _other.data[i]) {
			return(false);
		}
	}
	return(true);
}
bool Quaternion::operator!=(const Quaternion& _other) const
{
	return(!(this->data == _other.data));
}

Vector3  Quaternion::vector() const
{
	return((const Vector3&)(data));
}
Vector3&  Quaternion::vector()
{
	return((Vector3&)(data));

}

float  Quaternion::scalar() const
{
	return(w);
}
float&  Quaternion::scalar()
{
	return(w);
}

float  Quaternion::lengthSquared() const
{
	return(x*x + y*y + z*z + w*w);
}
float  Quaternion::length() const
{
	return(std::sqrt(lengthSquared()));
}

} // !namespace Challenge