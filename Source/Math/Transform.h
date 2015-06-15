#ifndef CHALLENGE_TRANSFORM_H
#define CHALLENGE_TRANSFORM_H

#include <Math\Math.h>

namespace Challenge {

struct Transform
{
	Vector3 position = Vector3(0, 0, 0);
	Quaternion orientation = Quaternion(0, 0, 0, 1);
	Vector3 scale = Vector3(1, 1, 1);

	Transform operator*(const Transform& _ls) const;
	Transform operator/(const Transform& _ps) const;
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
#endif // !#define CHALLENGE_TRANSFORM_H

