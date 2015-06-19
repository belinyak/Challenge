#ifndef CHALLENGE_CLOCK_H
#define CHALLENGE_CLOCK_H

#include <GLFW\glfw3.h>

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

