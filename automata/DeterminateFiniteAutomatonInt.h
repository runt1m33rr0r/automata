#pragma once

#include "SmartArray.h"
#include "State.h"

class DeterminateFiniteAutomatonInt
{
private:
	SmartArray<int> alphabet;
	SmartArray<State> states;

	State & getStateByName(const String & name);
	size_t findDanglingStateIdx(const SmartArray<State> & states) const;
	SmartArray<State> mergeRows(const SmartArray<State> & firstRow, const SmartArray<State> & secondRow) const;
public:
	DeterminateFiniteAutomatonInt();
	DeterminateFiniteAutomatonInt(const SmartArray<int> & alphabet);

	const State & getStarting() const;

	void setStarting(String name);
	void unsetStarting();
	void setFinal(String name);

	DeterminateFiniteAutomatonInt operator|(const DeterminateFiniteAutomatonInt & other) const;
};