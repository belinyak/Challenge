#include <Math\Vector3.h>

namespace Challenge
{

Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{}

Vector3::Vector3(f32 _xyz)
	: x(_xyz)
	, y(_xyz)
	, z(_xyz)
{}

Vector3::Vector3(f32 _x, f32 _y, f32 _z)
	: x(_x)
	, y(_y)
	, z(_z)
{}

Vector3::Vector3(f32 _xyz[3])
	: x(_xyz[0])
	, y(_xyz[1])
	, z(_xyz[2])
{}

} //namespace Challenge
