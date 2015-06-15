#include <Source\TickCounter.h>

namespace Challenge
{

bool TickCounter::update(double _frequency)
{
	bool reset = false;

	if (m_clock.getElapsedTime() >= _frequency)
	{
		//Note(mate): conversion from double to size_t warning ???
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

} // !namespace Challenge