#ifndef CHALLENGE_VERTEX_HPP
#define CHALLENGE_VERTEX_HPP
#include <Math\Math.hpp>
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
#endif // !#define CHALLENGE_VERTEX_HPP

