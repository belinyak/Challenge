#ifndef CHALLENGE_TRANSFORM_HPP
#define CHALLENGE_TRANSFORM_HPP

#include <Math\Math.hpp>

namespace Challenge {

struct Transform
{
	Vector3 position = Vector3(0, 0, 0);
	Quaternion orientation = Quaternion(0, 0, 0, 1);
	Vector3 scale = Vector3(1, 1, 1);

	Transform operator*(const Transform& _ls) const
	{
		Transform ws;
		ws.position = this->position + this->orientation * (this->scale * _ls.position);
		ws.orientation = this->orientation * _ls.orientation;
		ws.scale = this->scale * (this->orientation * _ls.scale);
		return(ws);
	}

	Transform operator/(const Transform& _ps) const
	{
		Transform ls;
		Quaternion _psConj = conjugate(_ps.orientation);
		ls.position = (_psConj * (this->position - _ps.position)) / _ps.scale;
		ls.orientation = _psConj * this->orientation;
		ls.scale = _psConj * (this->scale / _ps.scale);
		return(ls);
	}
};

inline Transform inverse(const Transform& _t) 
{
	const Transform default;
	return(default / _t);
}

inline Matrix4 transformMatrix4(const Transform& _t)
{
	return translate( _t.position) * quaternionToMatrix4(_t.orientation) * scale(_t.scale);
}

} // !namespace Challenge
#endif // !#define CHALLENGE_TRANSFORM_HPP

