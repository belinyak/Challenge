#ifndef CHALLENGE_VECTOR3_H
#define CHALLENGE_VECTOR3_H

#include <Source\Types.hpp>

namespace Challenge
{

struct Vector3
{
	Vector3();

	explicit Vector3(f32 _xyz);
	Vector3(f32 _x, f32 _y, f32 _z);
	Vector3(f32 _xyz[3]);

	f32& operator[](usize _index) { return data[_index]; }
	const f32& operator[](usize _index) const { return data[_index]; }

	union
	{
		f32 data[3];
		struct
		{
			f32 x, y, z;
		};
		struct
		{
			f32 r, g, b;
		};
		struct
		{
			f32 s, t, p;
		};
	};
};

} //namespace Challenge
#endif // !#define CHALLENGE_VECTOR3_H
