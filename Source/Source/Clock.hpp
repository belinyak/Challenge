#ifndef CHALLENGE_CLOCK_HPP
#define CHALLENGE_CLOCK_HPP

#include <GLFW\glfw3.h>
//TODO(mate): types.hhp-t kiszedni
//#include "Source\Types.hpp"

namespace Challenge
{

class Clock
{
public:
	inline double getElapsedTime() const
	{
		return((glfwGetTime() - m_startTime));
	}
	inline double restart()
	{
		double now = glfwGetTime();
		double elapsed = now - m_startTime;
		m_startTime = now;

		return(elapsed);
	}
private:
	double m_startTime = glfwGetTime();
};

} //namespace Challenge
#endif // !#define CHALLENGE_CLOCK_HPP

