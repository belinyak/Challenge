#ifndef CHALLENGE_VERTEX_H
#define CHALLENGE_VERTEX_H
#include <Math\Math.h>
#include <Source\Color.hpp>

namespace Challenge
{
struct Vertex
{
	Vector3 position;
	Color color;
	Vector2 texCoord;
};
} //!namespace Challenge
#endif // !#define CHALLENGE_VERTEX_H

