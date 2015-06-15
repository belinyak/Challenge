#ifndef CHALLENGE_TICKCOUNTER_H
#define CHALLENGE_TICKCOUNTER_H

#include <Source\Clock.h>
#include <Source\Types.hpp>

namespace Challenge
{
class TickCounter
{
public:
	bool update(double _frequency);
	std::size_t getTickRate() const;
private:
	std::size_t m_tick;
	std::size_t m_tickRate;
	Clock m_clock;
};
} // !namespace Challenge
#endif // !#define CHALLENGE_TICKCOUNTER_H