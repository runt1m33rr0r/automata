#include "DeterminateFiniteAutomatonInt.h"

DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt()
{
}

DeterminateFiniteAutomatonInt::DeterminateFiniteAutomatonInt(const SmartArray<int>& alphabet)
	: alphabet(alphabet)
{
}

State & DeterminateFiniteAutomatonInt::getStateByName(const String & name)
{
	for (size_t i = 0; i < this->states.getCount(); i++)
	{
		if (this->states[i].getName() == name)
		{
			return this->states[i];
		}
	}

	throw std::exception("State does not exist!");
}

size_t DeterminateFiniteAutomatonInt::findDanglingStateIdx() const
{
	for (size_t stateIdx = 0; stateIdx < this->states.getCount(); stateIdx++)
	{
		for (size_t row = 0; row < this->transitionTable.getCount(); row++)
		{
			if (this->transitionTable[row].indexOf(this->states[stateIdx]))
			{
				return stateIdx;
			}
		}
	}

	return -1;
}

SmartArray<State> DeterminateFiniteAutomatonInt::mergeRows(
	const SmartArray<State>& firstRow, 
	const SmartArray<State>& secondRow,
	MergeMode mode)
{
	SmartArray<State> newRow;

	for (size_t i = 0; i < firstRow.getCount(); i++)
	{
		State first = firstRow[i];
		State second = secondRow[i];
		State merged = DeterminateFiniteAutomatonInt::mergeStates(first, second, mode);

		newRow.add(merged);
	}

	return newRow;
}

State DeterminateFiniteAutomatonInt::mergeStates(const State & first, const State & second, MergeMode mode)
{
	String newStateName = first.getName() + " " + second.getName();
	bool isStarting = first.getStarting() && second.getStarting();
	bool isFinal = false;
	if (mode == MergeMode::Union)
	{
		isFinal = first.getFinal() || second.getFinal();
	}
	else
	{
		isFinal = first.getFinal() && second.getFinal();
	}

	SmartArray<State> composite;
	composite.add(first);
	composite.add(second);

	return State(newStateName, isStarting, isFinal, composite);
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::mergeAutomata(
	const DeterminateFiniteAutomatonInt & first,
	const DeterminateFiniteAutomatonInt & second,
	MergeMode mode)
{
	DeterminateFiniteAutomatonInt newAutomaton(first.alphabet);
	State mergedState = DeterminateFiniteAutomatonInt::mergeStates(
		first.getStartingState(),
		second.getStartingState(), MergeMode::Union);

	SmartArray<State> mergedFirstRow = DeterminateFiniteAutomatonInt::mergeRows(
		first.transitionTable[0],
		second.transitionTable[0],
		MergeMode::Union);
	newAutomaton.states.add(mergedState);
	newAutomaton.transitionTable.add(mergedFirstRow);

	size_t danglingStateIdx;
	State danglingState;
	size_t firstRowIdx;
	size_t secondRowIdx;
	SmartArray<State> firstRow;
	SmartArray<State> secondRow;
	SmartArray<State> mergedRow;

	do
	{
		danglingStateIdx = newAutomaton.findDanglingStateIdx();
		danglingState = newAutomaton.states[danglingStateIdx];

		firstRowIdx = first.states.indexOf(danglingState.getCompositeStates()[0]);
		secondRowIdx = second.states.indexOf(danglingState.getCompositeStates()[1]);
		firstRow = first.transitionTable[firstRowIdx];
		secondRow = second.transitionTable[secondRowIdx];

		mergedRow = DeterminateFiniteAutomatonInt::mergeRows(firstRow, secondRow, MergeMode::Union);
		newAutomaton.transitionTable.add(mergedRow);
	} while (danglingStateIdx >= 0);

	return newAutomaton;
}

const State & DeterminateFiniteAutomatonInt::getStartingState() const
{
	for (size_t i = 0; i < this->states.getCount(); i++)
	{
		if (this->states[i].getStarting())
		{
			return this->states[i];
		}
	}

	throw std::exception("State does not exist!");
}

void DeterminateFiniteAutomatonInt::setStartingState(String name)
{
	if (this->getStartingState().getStarting())
	{
		throw std::exception("Automaton already has starting state!");
	}

	this->getStateByName(name).setStarting(true);
}

void DeterminateFiniteAutomatonInt::unsetStartingState()
{
	String startingName = this->getStartingState().getName();
	this->getStateByName(startingName).setStarting(false);
}

void DeterminateFiniteAutomatonInt::setFinalState(String name)
{
	this->getStateByName(name).setFinal(true);
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::operator|(
	const DeterminateFiniteAutomatonInt & other) const
{
	return DeterminateFiniteAutomatonInt::mergeAutomata(*this, other, MergeMode::Union);
}
