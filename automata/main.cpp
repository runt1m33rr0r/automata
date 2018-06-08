#include <iostream>
#include <exception>

#include "DeterminateFiniteAutomatonInt.h"

using namespace std;

int main()
{
	unsigned statesCount = 2;
	/*cout << "number of states: ";
	cin >> statesCount;*/

	SmartArray<State> states;
	states.add(State("q0"));
	states.add(State("q1"));
	states.add(State("q2"));
	states.add(State("q3"));
	/*for (size_t i = 0; i < statesCount; i++)
	{
		String stateName;
		cout << "state" << i << " name: ";
		cin >> stateName;

		states.add(State(stateName));
	}*/

	unsigned symbolsCount = 2;
	//cout << "number of symbols: ";
	//cin >> symbolsCount;

	SmartArray<String> symbols;
	symbols.add("0");
	symbols.add("1");
	/*for (size_t i = 0; i < symbolsCount; i++)
	{
		String symbol;
		cout << "symbol" << i << " name: ";
		cin >> symbol;

		symbols.add(symbol);
	}*/

	SmartArray<SmartArray<State>> transitionTable;

	SmartArray<State> firstRow;
	firstRow.add(State("q0"));
	firstRow.add(State("q1"));
	transitionTable.add(firstRow);

	SmartArray<State> secondRow;
	secondRow.add(State("q1"));
	secondRow.add(State("q1"));
	transitionTable.add(secondRow);

	/*for (size_t stateIdx = 0; stateIdx < statesCount; stateIdx++)
	{
		SmartArray<State> rowStates;
		for (size_t symbolIdx = 0; symbolIdx < symbolsCount; symbolIdx++)
		{
			cout << "transition (" << states[stateIdx].getName() << ", " << symbols[symbolIdx] << ")->";
			String toName;
			cin >> toName;
			rowStates.add(State(toName));
		}

		transitionTable.add(rowStates);
	}*/

	cout << "  ";
	for (size_t i = 0; i < symbolsCount; i++)
	{
		cout << "  " << symbols[i];
	}
	cout << endl;

	for (size_t i = 0; i < statesCount; i++)
	{
		cout << states[i].getName() << " ";
		for (size_t j = 0; j < symbolsCount; j++)
		{
			cout << transitionTable[i][j].getName() << " ";
		}
		cout << endl;
	}

	return 0;
}
