#ifndef CHALLENGE_MATH_MATRIX_H
#define CHALLENGE_MATH_MATRIX_H

#include <cmath>

#include <Math\Vector3.h>
#include <Math\Matrix4.h>
#include <Math\Angle.h>


//Note(mate): All the matrix functions

/* 
 *translate		http://en.wikipedia.org/wiki/Transformation_matrix
 *rotate		http://en.wikipedia.org/wiki/Rotation_matrix
 *scale			http://en.wikipedia.org/wiki/Scaling_(geometry)
 *ortho			http://en.wikipedia.org/wiki/Orthographic_projection
 *perspective	        http://en.wikipedia.org/wiki/Transformation_matrix#Perspective_projection
 *look at
 */

Matrix4 translate(const Vector3& _v);
Matrix4 rotate(const float& _angle, const Vector3& _v);
Matrix4 scale(const Vector3& _v);
			
Matrix4 perspective(const float& _fovy, float _aspect,
		    float _zNear, float _zFar);

Matrix4 lookAtit(const Vector3& _eye, const Vector3& center, const Vector3& up);
#endif
