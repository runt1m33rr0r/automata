#pragma once

#include "SmartArray.h"
#include "State.h"

class DeterminateFiniteAutomatonInt
{
private:
	SmartArray<String> alphabet;
	SmartArray<State> states;
public:
	size_t getIndexOfStarting() const;

	void setStartingAt(size_t idx);
};