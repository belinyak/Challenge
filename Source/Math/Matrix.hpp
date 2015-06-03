#ifndef CHALLENGE_MATRIX_GUARD
#define CHALLENGE_MATRIX_GUARD

#include <Math\Vector3.hpp>
#include <Math\Matrix4.hpp>
#include <cmath>

//Note(mate): All the matrix functions

namespace Challenge
{

/* TODO(mate):	translate 
				rotate
				scale
				ortho
				percpective
				look at
*/

inline Matrix4
translate(const Vector3& _v)
{
	Matrix4 result;
	result[3] = Vector4(_v, 1);
	return result;

}

inline Matrix4 
rotate(float _angle, const Vector3& _v)
{

	const f32 c = std::cos(_angle);
	const f32 s = std::sin(_angle);

	const Vector3 axis(normalized(_v));
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

inline Matrix4
scale(const Vector3& _v)
{
	Matrix4 result(
	    {_v.x, 0, 0, 0}, { 0, _v.y, 0, 0 }, { 0, 0, _v.z, 0 }, { 0, 0, 0, 1 });
	return result;
}

} //!namespace Challenge

#endif // !#define CHALLENGE_MATRIX_GUARD

