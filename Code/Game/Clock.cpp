#include <Game\Clock.h>

double Clock::getElapsedTime() const
{  
    return((glfwGetTime() - m_startTime));
}

double Clock::restart()
{
	double now = glfwGetTime();
	double elapsed = now - m_startTime;
	m_startTime = now;

	return(elapsed);
}

