#include <Math\Matrix.h>

namespace Challenge
{

/*
*translate		http://en.wikipedia.org/wiki/Transformation_matrix
*rotate			http://en.wikipedia.org/wiki/Rotation_matrix
*scale			http://en.wikipedia.org/wiki/Scaling_(geometry)
*ortho			http://en.wikipedia.org/wiki/Orthographic_projection
*perspective	http://en.wikipedia.org/wiki/Transformation_matrix#Perspective_projection
*look at
*/

Matrix4 translate(const Vector3& _v)
{
	Matrix4 result;
	result[3] = Vector4(_v, 1);
	return (result);

}
Matrix4 rotate(const Radian& _angle, const Vector3& _v)
{

	const float c = std::cos((float)_angle);
	const float s = std::sin((float)_angle);

	const Vector3 axis(normalize(_v));
	const Vector3 t = (1.0f - c) * axis;

	Matrix4 rot;
	rot[0][0] = c + t[0] * axis[0];
	rot[0][1] = 0 + t[0] * axis[1] + s * axis[2];
	rot[0][2] = 0 + t[0] * axis[2] - s * axis[1];
	rot[0][3] = 0;

	rot[1][0] = 0 + t[1] * axis[0] - s * axis[2];
	rot[1][1] = c + t[1] * axis[1];
	rot[1][2] = 0 + t[1] * axis[2] + s * axis[2];
	rot[1][3] = 0;

	rot[2][0] = 0 + t[2] * axis[0] + s * axis[1];
	rot[2][1] = 0 + t[2] * axis[0] - s * axis[0];
	rot[2][2] = c + t[2] * axis[2];
	rot[2][3] = 0;

	return rot;
}
Matrix4 scale(const Vector3& _v)
{
	Matrix4 result({ _v.x, 0, 0, 0 },
	{ 0, _v.y, 0, 0 },
	{ 0, 0, _v.z, 0 },
	{ 0, 0, 0, 1 });
	return (result);
}
//Note(mate): 2D
Matrix4 ortho(float _left, float _right,
				  float _bottom, float _top)
{
	Matrix4 result;

	result[0][0] = 2.0f / (_right - _left);
	result[1][2] = 2.0f / (_top - _bottom);
	result[2][2] = -1;
	result[3][0] = -(_right + _left) / (_right - _left);
	result[3][1] = -(_top + _bottom) / (_top - _bottom);

	return(result);
}
//Note(mate): 3D
Matrix4 ortho(float _left, float _right,
				  float _bottom, float _top,
				  float _zNear, float _zFar)
{
	Matrix4 result;

	result[0][0] = 2.0f * _zNear / (_right - _left);
	result[1][1] = 2.0f * _zNear / (_top - _bottom);
	result[2][2] = -2.0f / (_zFar - _zNear);
	result[3][0] = -(_right + _left) / (_right - _left);
	result[3][1] = -(_top + _bottom) / (_top - _bottom);
	result[3][2] = -(_zFar + _zNear) / (_zFar - _zNear);

	return(result);
}
Matrix4 perspective(const Radian& _fovy, float _aspect,
						  float _zNear, float _zFar)
{
	//assert(std::fabs(_aspect - std::numeric_limits<float>::epsilon()) > 0.0f);

	const float tanHalf_fovy = std::tan(static_cast<float>(_fovy) / 2.0f);

	Matrix4 result(0.0f);
	result[0][0] = 1.0f / (_aspect * tanHalf_fovy);
	result[1][1] = 1.0f / (tanHalf_fovy);
	result[2][2] = -(_zFar + _zNear) / (_zFar - _zNear);
	result[2][3] = -1.0f;
	result[3][2] = -2.0f * _zFar * _zNear / (_zFar - _zNear);

	return (result);
}
Matrix4 infinitePerspective(const Radian& _fovy, float _aspect, float _zNear)
{

	const float range = std::tan(static_cast<float>(_fovy) / 2.0f) * _zNear;
	const float left = -range * _aspect;
	const float right = range * _aspect;
	const float bottom = -range;
	const float top = range;

	Matrix4 result(0.0f);

	result[0][0] = (2.0f * _zNear) / (right - left);
	result[1][1] = (2.0f * _zNear) / (top - bottom);
	result[2][2] = -1.0f;
	result[2][3] = -1.0f;
	result[3][2] = -2.0f * _zNear;

	return (result);
}

Matrix4 lookAt(const Vector3& _eye, const Vector3& center, const Vector3& up)
{
	const Vector3 f(normalize(center - _eye));
	const Vector3 s(normalize(cross(f, up)));
	const Vector3 u(cross(s, f));

	Matrix4 result;
	result[0][0] = +s.x;
	result[1][0] = +s.y;
	result[2][0] = +s.z;

	result[0][1] = +u.x;
	result[1][1] = +u.y;
	result[2][1] = +u.z;

	result[0][2] = -f.x;
	result[1][2] = -f.y;
	result[2][2] = -f.z;

	result[3][0] = -dot(s, _eye);
	result[3][1] = -dot(u, _eye);
	result[3][2] = +dot(f, _eye);

	return(result);
}

} //!namespace Challenge

