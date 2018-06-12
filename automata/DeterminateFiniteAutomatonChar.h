#pragma once

#include <fstream>

#include "DeterminateFiniteAutomaton.h"

class DeterminateFiniteAutomatonChar : public DeterminateFiniteAutomaton<char>
{
public:
	DeterminateFiniteAutomatonChar(
		const SmartArray<char> & alphabet,
		const SmartArray<State> & states,
		const TransitionTable & table);

	virtual std::ofstream & insertDataInFile(std::ofstream & out) const;
};