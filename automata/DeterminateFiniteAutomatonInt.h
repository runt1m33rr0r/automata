#pragma once

#include <fstream>

#include "SmartArray.h"
#include "State.h"

enum MergeMode { Union, Intersection };

typedef SmartArray<SmartArray<State>> TransitionTable;

class DeterminateFiniteAutomatonInt
{
private:
	SmartArray<char> alphabet;
	SmartArray<State> states;
	TransitionTable transitionTable;

	State & getStateByName(const String & name);
	const State * findDanglingState() const;
	SmartArray<State> getFinalStates() const;

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
	DeterminateFiniteAutomatonInt(
		const SmartArray<char> & alphabet,
		const SmartArray<State>& states,
		TransitionTable & transitionTable);

	const State & getStartingState() const;

	void setStartingState(String name);
	void unsetStartingState();
	void setFinalState(String name);

	bool doesRecognizeWord(const String & word) const;

	DeterminateFiniteAutomatonInt operator|(const DeterminateFiniteAutomatonInt & other) const;
	DeterminateFiniteAutomatonInt operator&(const DeterminateFiniteAutomatonInt & other) const;
	DeterminateFiniteAutomatonInt operator^(const DeterminateFiniteAutomatonInt & other) const;

	std::ostream & insertDataInStream(std::ostream & out) const;
	std::istream & extractDataFromStream(std::istream & in);
	std::ofstream & insertDataInFile(std::ofstream & out) const;
	std::ifstream & extractDataFromFile(std::ifstream & in);
};

std::ostream & operator<<(std::ostream & out, const DeterminateFiniteAutomatonInt & obj);
std::istream & operator>>(std::istream & in, DeterminateFiniteAutomatonInt & obj);

std::ofstream & operator<<(std::ofstream & out, const DeterminateFiniteAutomatonInt & obj);
std::ifstream & operator>>(std::ifstream & in, DeterminateFiniteAutomatonInt & obj);