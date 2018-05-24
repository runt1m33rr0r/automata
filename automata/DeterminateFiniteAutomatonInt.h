#pragma once

#include "SmartArray.h"
#include "State.h"

class DeterminateFiniteAutomatonInt
{
private:
	SmartArray<String> alphabet;
	SmartArray<State> states;
	State startState;
	SmartArray<State> finalStates;
};