#include "DeterminateFiniteAutomatonInt.h"

size_t DeterminateFiniteAutomatonInt::getIndexOfStarting() const
{
	for (size_t i = 0; i < this->states.getCount(); i++)
	{
		if (this->states[i].getStarting())
		{
			return i;
		}
	}

	return -1;
}

void DeterminateFiniteAutomatonInt::setStartingAt(size_t idx)
{
	size_t oldStarting = this->getIndexOfStarting();
	if (oldStarting > -1)
	{
		this->states[oldStarting].setStarting(false);
	}

	this->states[idx].setStarting(true);
}
