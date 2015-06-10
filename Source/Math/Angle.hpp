#ifndef CHALLENGE_ANGLE_HPP
#define CHALLENGE_ANGLE_HPP

#include <Math\Unit.hpp>
#include <Math\Constants.hpp>
#include <ostream>

namespace Challenge { namespace Impl {
template <class T>
class Radian;

// Degree  
template <class T>
class Degree : public Unit<Degree, T>
{
public:
Degree() {}

explicit Degree(T _value)
: Unit<Challenge::Impl::Degree, T>(_value)
{
}

Degree(Unit<Challenge::Impl::Degree, T> _value)
: Unit<Challenge::Impl::Degree, T>(_value)
{
}

template <class U>
explicit Degree(Unit<Challenge::Impl::Degree, U> _value)
: Unit<Challenge::Impl::Degree, T>(_value)
{
}

Degree(Unit<Radian, T> _value);
};

// Radian  
template <class T>
class Radian : public Unit<Radian, T>
{
public:
Radian() {}

explicit Radian(T _value)
: Unit<Challenge::Impl::Radian, T>(_value)
{
}

Radian(Unit<Challenge::Impl::Radian, T> _value)
: Unit<Challenge::Impl::Radian, T>(_value)
{
}
template <class U>
explicit Radian(Unit<Challenge::Impl::Radian, U> _value)
: Unit<Challenge::Impl::Radian, T>(_value)
{
}

Radian(Unit<Degree, T> _value);
};

template <class T>
Degree<T>::Degree(Unit<Radian, T> _value)
: Unit<Challenge::Impl::Degree, T>(T(360) * T(_value) / T(Constants::TAU))
{
}
template <class T>
Radian<T>::Radian(Unit<Degree, T> _value)
: Unit<Challenge::Impl::Radian, T>(T(_value) * T(Constants::TAU) / T(360))
{}

} //!namespace Impl  

using Radian = Impl::Radian<float>;
using Degree = Impl::Degree<float>;

} //!namespace Challenge
#endif // !#define CHALLENGE_ANGLE_HPP

