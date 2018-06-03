#pragma once

#include "SmartArray.h"
#include "State.h"

class DeterminateFiniteAutomatonInt
{
private:
	SmartArray<int> alphabet;
	SmartArray<State> states;

	State & getStateByName(const String & name);
public:
	DeterminateFiniteAutomatonInt();
	DeterminateFiniteAutomatonInt(const SmartArray<int> & alphabet);

	const State & getStarting() const;

	void setStarting(String name);
	void unsetStarting();
	void setFinal(String name);
};