#ifndef CHALLENGE_UNIT_HPP
#define CHALLENGE_UNIT_HPP

#include <cmath>
#include <chrono>

namespace Challenge
{

template <template <class> class Derived, class T>
class Unit
{
	template <template <class> class, class>
	friend class Unit;

public:
	typedef T Type;

	Unit()
	: m_value(T(0))
	{}
	
	explicit Unit(T _value)
	: m_value(_value)
	{}

	template <class U>
	explicit Unit(Unit<Derived, U> _value)
						: m_value(T(_value.m_value))
	{}

	explicit operator T() const { return m_value; }

	bool operator==(Unit<Derived, T> _other) const {
		return m_value == _other.m_value;
	}

	bool operator!=(Unit<Derived, T> _other) const { 
		return !operator==(_other); 
	}

	bool operator<(Unit<Derived, T> _other) const {
		return m_value < _other.m_value;
	}

	bool operator>(Unit<Derived, T> _other) const {
		return m_value > _other.m_value;
	}

	bool operator<=(Unit<Derived, T> _other) const { 
		return !operator>(_other);
	}

	bool operator>=(Unit<Derived, T> _other) const {
		return !operator<(_other);
	}

	Unit<Derived, T> operator-() const {
		return Unit<Derived, T>(-m_value);
	}

	Unit<Derived, T>& operator+=(Unit<Derived, T> _other)
	{
		m_value += _other.m_value;
		return *this;
	}

	Unit<Derived, T> operator+(Unit<Derived, T> _other) const	{
		return Unit<Derived, T>(m_value + _other.m_value);
	}

	Unit<Derived, T>& operator-=(Unit<Derived, T> _other)
	{
		m_value -= _other.m_value;
		return *this;
	}

	Unit<Derived, T> operator-(Unit<Derived, T> _other) const	{
		return Unit<Derived, T>(m_value - _other.m_value);
	}

	Unit<Derived, T>& operator*=(T _number)
	{
		m_value *= _number;
		return *this;
	}

	Unit<Derived, T> operator*(T _number) const	{
		return Unit<Derived, T>(m_value * _number);
	}

	Unit<Derived, T>& operator/=(T _number)
	{
		m_value /= _number;
		return *this;
	}

	Unit<Derived, T> operator/(T _number) const	{
 		return Unit<Derived, T>(m_value / _number);
 	}

 	T operator/(Unit<Derived, T> _other) const { 
		return m_value / _other.value; 
	}

 private:
 	T m_value;
 };

 template <template <class> class Derived, class T>
 Unit<Derived, T> operator*(typename std::common_type<T>::type _number,
									       const Unit<Derived, T>& _value) {
 	return _value * _number;
 }

} //!namespace Challenge
#endif // !#define CHALLENGE_UNIT_HPP

