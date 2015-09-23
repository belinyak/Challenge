#include <Math\Vector4.h>

Vector4::Vector4()
	: x(0)
	, y(0)
	, z(0)
	, w(0)
{}
Vector4::Vector4(float xyzw)
	: x(xyzw)
	, y(xyzw)
	, z(xyzw)
	, w(xyzw)
{}
Vector4::Vector4(float x, float y, float z, float w)
	: x(x)
	, y(y)
	, z(z)
	, w(w)
{}
Vector4::Vector4(float xyzw[4])
	: x(xyzw[0])
	, y(xyzw[1])
	, z(xyzw[2])
	, w(xyzw[3])
{}

Vector4::Vector4(const Vector2& xy, float z, float w)
	: x(xy.x)
	, y(xy.y)
	, z(z)
	, w(w)
{}
Vector4::Vector4(const Vector2& xy, const Vector2& zw)
	: x(xy.x)
	, y(xy.y)
	, z(zw.x)
	, w(zw.y)
{}
Vector4::Vector4(const Vector3& xyz, float w)
	: x(xyz.x)
	, y(xyz.y)
	, z(xyz.z)
	, w(w)
{}

Vector4 Vector4::operator-() const {
	return{ -x,-y,-z,-w };
}

bool Vector4::operator==(const Vector4& other) const
{
	for (std::size_t i = 0; i < 4; i++)
	{
		if (data[i] != other.data[i]) {
			return(false);
		}
	}
	return(true);
}
bool Vector4::operator!=(const Vector4& other) const {
	return((!operator==(other)));
}

Vector4 Vector4::operator+(const Vector4& other) const {
	return((Vector4(x + other.x, y + other.y, z + other.z, w + other.w)));
}
Vector4 Vector4::operator-(const Vector4& other) const {
	return((Vector4(x - other.x, y - other.y, z - other.z, w - other.w)));
}
Vector4 Vector4::operator*(float scalar) const {
	return((Vector4(scalar * x, scalar * y, scalar * z, scalar * w)));
}
