#ifndef CHALLENGE_MATH_MATRIX_HPP
#define CHALLENGE_MATH_MATRIX_HPP

//TODO(mate): separate to .h and .cpp

#include <Math\Vector3.hpp>
#include <Math\Matrix4.hpp>
#include <Math\Angle.hpp>

#include <cmath>

//Note(mate): All the matrix functions

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

Matrix4 translate(const Vector3& _v);
Matrix4 rotate(const Radian& _angle, const Vector3& _v);
Matrix4 scale(const Vector3& _v);
//Note(mate): 2D
Matrix4 ortho(float _left, float _right,
				  float _bottom, float _top);
//Note(mate): 3D
Matrix4 ortho(float _left, float _right,
				  float _bottom, float _top,
				  float _zNear, float _zFar);
Matrix4 perspective(const Radian& _fovy, f32 _aspect,
						  float _zNear, float _zFar);
Matrix4 infinitePerspective(const Radian& _fovy, f32 _aspect, f32 _zNear);

Matrix4 lookAt(const Vector3& _eye, const Vector3& center, const Vector3& up);
} // !namespace Challenge
#endif
