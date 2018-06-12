#include "DeterminateFiniteAutomatonInt.h"

DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(
	const SmartArray<int>& alphabet,
	const SmartArray<State>& states,
	const TransitionTable & table) : DeterminateFiniteAutomaton<int>(alphabet, states, table)
{
}

std::ofstream & DeterminateFiniteAutomatonInt::insertDataInFile(std::ofstream & out) const
{
	// print alphabet type
	out << "1" << std::endl;
	DeterminateFiniteAutomaton<int>::insertDataInFile(out);
	return out;
}