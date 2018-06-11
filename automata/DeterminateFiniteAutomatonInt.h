#pragma once

#include "SmartArray.h"
#include "State.h"

enum MergeMode { Union, Intersection };

typedef SmartArray<SmartArray<State>> TransitionTable;

class DeterminateFiniteAutomatonInt
{
private:
	SmartArray<int> alphabet;
	SmartArray<State> states;
	TransitionTable transitionTable;

	State & getStateByName(const String & name);
	size_t findDanglingStateIdx() const;

	static SmartArray<State> mergeRows(
		const SmartArray<State> & firstRow,
		const SmartArray<State> & secondRow,
		MergeMode mode);
	static State mergeStates(const State & first, const State & second, MergeMode mode);
	static DeterminateFiniteAutomatonInt mergeAutomata(
		const DeterminateFiniteAutomatonInt & first, 
		const DeterminateFiniteAutomatonInt & second,
		MergeMode mode);
public:
	DeterminateFiniteAutomatonInt();
	DeterminateFiniteAutomatonInt(const SmartArray<int> & alphabet);

	const State & getStartingState() const;

	void setStartingState(String name);
	void unsetStartingState();
	void setFinalState(String name);

	DeterminateFiniteAutomatonInt operator|(const DeterminateFiniteAutomatonInt & other) const;
};