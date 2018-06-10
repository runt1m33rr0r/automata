#include "State.h"

State::State() : name("none"), isFinal(false), isStarting(false)
{
}

State::State(const String & name, bool isStarting, bool isFinal) :
	name(name), isFinal(isFinal), isStarting(isStarting)
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

void State::setStarting(bool isStarting)
{
	this->isStarting = isStarting;
}

void State::setFinal(bool isFinal)
{
	this->isFinal = isFinal;
}
