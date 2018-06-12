#pragma once

#include <fstream>

#include "DeterminateFiniteAutomaton.h"

class DeterminateFiniteAutomatonInt : public DeterminateFiniteAutomaton<int>
{
public:
	DeterminateFiniteAutomatonInt(
		const SmartArray<int> & alphabet,
		const SmartArray<State> & states,
		const TransitionTable & table);

	virtual std::ofstream & insertDataInFile(std::ofstream & out) const;
};