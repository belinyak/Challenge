#include <Game\TickCounter.h>

bool TickCounter::update(double _frequency)
{
	bool reset = false;

	if (m_clock.getElapsedTime() >= _frequency)
	{
		m_tickRate = m_tick / _frequency;
		m_tick = 0;
		reset = true;
		m_clock.restart();
	}
	m_tick++;

	return(reset);
}
std::size_t TickCounter::getTickRate() const {
	return(m_tickRate);
}

