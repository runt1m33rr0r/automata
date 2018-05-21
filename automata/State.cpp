#include "State.h"

State::State() : name("")
{
}

State::State(const String & name) : name(name)
{
}

String State::getName() const
{
	return this->name;
}