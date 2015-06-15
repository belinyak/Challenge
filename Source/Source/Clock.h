#ifndef CHALLENGE_CLOCK_H
#define CHALLENGE_CLOCK_H

//TODO(mate): Inline functions?

#include <GLFW\glfw3.h>
//TODO(mate): remove Types.hpp
//#include "Source\Types.hpp"

namespace Challenge
{
class Clock
{
public:
	double getElapsedTime() const;
	double restart();
private:
	double m_startTime = glfwGetTime();
};

} //namespace Challenge
#endif // !#define CHALLENGE_CLOCK_H

