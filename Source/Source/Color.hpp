#ifndef CHALLENGE_COLOR_HPP
#define CHALLENGE_COLOR_HPP

#include <Source\Types.hpp>

namespace Challenge
{

union Color
{
	u8 data[4];
	struct MyStruct
	{
		u8 r, g, b, a;
	};
};

} //!namespace Challenge

#endif // !#define CHALLENGE_COLOR_HPP

