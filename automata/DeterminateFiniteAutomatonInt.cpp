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

size_t DeterminateFiniteAutomatonInt::findDanglingStateIdx(const SmartArray<State>& states) const
{
	for (size_t i = 0; i < states.getCount(); i++)
	{
		if (this->states.indexOf(states[i]) == false);
		{
			return i;
		}
	}

	return -1;
}

SmartArray<State> DeterminateFiniteAutomatonInt::mergeRows(const SmartArray<State>& firstRow, const SmartArray<State>& secondRow) const
{
	SmartArray<State> newRow;

	for (size_t i = 0; i < firstRow.getCount(); i++)
	{
		State first = firstRow[i];
		State second = secondRow[i];
		String newName = first.getName() + second.getName();

		if (i == 0)
		{
			newRow.add(State(newName, false, true));
		}
		else
		{
			newRow.add(State(newName));
		}
	}

	return newRow;
}

const State & DeterminateFiniteAutomatonInt::getStarting() const
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

void DeterminateFiniteAutomatonInt::setStarting(String name)
{
	if (this->getStarting().getStarting())
	{
		throw std::exception("Automaton already has starting state!");
	}

	this->getStateByName(name).setStarting(true);
}

void DeterminateFiniteAutomatonInt::unsetStarting()
{
	String startingName = this->getStarting().getName();
	this->getStateByName(startingName).setStarting(false);
}

void DeterminateFiniteAutomatonInt::setFinal(String name)
{
	this->getStateByName(name).setFinal(true);
}

DeterminateFiniteAutomatonInt DeterminateFiniteAutomatonInt::operator|(const DeterminateFiniteAutomatonInt & other) const
{


	return DeterminateFiniteAutomatonInt();
}
