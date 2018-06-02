#include "State.h"

State::State() : name(""), isFinal(false), isStarting(false)
{
}

State::State(const String & name, bool isFinal, bool isStarting) : 
	name(name), isFinal(isFinal), isStarting(isStarting)
{
}

String State::getName() const
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
