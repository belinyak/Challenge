#ifndef CHALLENGE_COLOR_HPP
#define CHALLENGE_COLOR_HPP


union Color
{
	std::uint8_t data[4];
	struct MyStruct
	{
		std::uint8_t r, g, b, a;
	};
};

#endif // !#define CHALLENGE_COLOR_HPP