#include "DeterminateFiniteAutomatonChar.h"

DeterminateFiniteAutomatonChar::DeterminateFiniteAutomatonChar(
	const SmartArray<char>& alphabet, 
	const SmartArray<State>& states, 
	const TransitionTable & table) : DeterminateFiniteAutomaton<char>(alphabet, states, table)
{
}

std::ofstream & DeterminateFiniteAutomatonChar::insertDataInFile(std::ofstream & out) const
{
	// print alphabet type
	out << "2" << std::endl;
	DeterminateFiniteAutomaton<char>::insertDataInFile(out);
	return out;
}
