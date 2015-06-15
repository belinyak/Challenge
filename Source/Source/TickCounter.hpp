#ifndef CHALLENGE_TICKCOUNTER_HPP
#define CHALLENGE_TICKCOUNTER_HPP

#include <Source\Clock.hpp>
#include <Source\Types.hpp>

namespace Challenge
{
class TickCounter
{
public:
	bool update(double _frequency)
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
	inline std::size_t getTickRate() const {
		return(m_tickRate);
	}
private:
	std::size_t m_tick;
	std::size_t m_tickRate;
	Clock m_clock;
};
} // !namespace Challenge
#endif // !#define CHALLENGE_TICKCOUNTER_HPP