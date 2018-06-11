#include "State.h"
#include "String.h"

State::State() : name("none"), isFinal(false), isStarting(false)
{
}

State::State(const String & name, bool isStarting, bool isFinal, const SmartArray<State> & compositeStates) :
	name(name), isFinal(isFinal), isStarting(isStarting), compositeStates(compositeStates)
{
}

const String & State::getName() const
{
	return this->name;
}

bool State::getFinal() const
{
	return this->isFinal;
}

bool State::getStarting() const
{
	return this->isStarting;
}

SmartArray<State> State::getCompositeStates() const
{
	return this->compositeStates;
}

void State::setStarting(bool isStarting)
{
	this->isStarting = isStarting;
}

void State::setFinal(bool isFinal)
{
	this->isFinal = isFinal;
}

bool State::operator==(const State & other) const
{
	if (this == &other)
	{
		return true;
	}
	
	if (this->name == other.name)
	{
		return true;
	}

	return false;
}
