#pragma once

#include <iostream>

namespace model
{

template<typename T>
class Optional
{
public:

	Optional() :_isSet(false){}

	Optional(const T &value) :_isSet(false)
	{
		_value = value;
	}

	Optional(T &&value) :_isSet(false)
	{
		_value = std::move(value);
	}

	Optional &operator = (const T &value)
	{
		_value = value;
		_isSet = true;
		return *this;
	}

	Optional &operator = (T &&value)
	{
		_value = value;//std::move(value);
		_isSet = true;
		return *this;
	}

	T &value()
	{
		return _value;
	}

	const T &value() const
	{
		return _value;
	}

	bool isSet() const
	{
		return _isSet;
	}

	bool operator == (const Optional<T> &rhs) const
	{
		return (_isSet == rhs._isSet) && (_value == rhs._value);
	}

private:

	T _value;
	bool _isSet;
};

}