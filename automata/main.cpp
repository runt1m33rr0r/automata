#include <iostream>
#include <exception>

#include "DeterminateFiniteAutomatonInt.h"

using namespace std;

int main()
{
	SmartArray<char> alphabet;
	alphabet.add('a');
	alphabet.add('b');

	SmartArray<State> firstStates;
	firstStates.add(State("q0", true));
	firstStates.add(State("q1", false, true));

	TransitionTable firstTransitions;
	firstTransitions.add(SmartArray<State>());
	firstTransitions.add(SmartArray<State>());
	firstTransitions[0].add(State("q1", false, true));
	firstTransitions[0].add(State("q0", true));
	firstTransitions[1].add(State("q0", true));
	firstTransitions[1].add(State("q1", false, true));

	DeterminateFiniteAutomatonInt first(alphabet, firstStates, firstTransitions);
	cout << first;

	SmartArray<State> secondStates;
	secondStates.add(State("q0", true));
	secondStates.add(State("q1"));
	secondStates.add(State("q2"));
	secondStates.add(State("q3", false, true));

	TransitionTable secondTransitions;
	secondTransitions.add(SmartArray<State>());
	secondTransitions.add(SmartArray<State>());
	secondTransitions.add(SmartArray<State>());
	secondTransitions.add(SmartArray<State>());
	secondTransitions[0].add(State("q1"));
	secondTransitions[0].add(State("q0", true));
	secondTransitions[1].add(State("q1"));
	secondTransitions[1].add(State("q2"));
	secondTransitions[2].add(State("q3", false, true));
	secondTransitions[2].add(State("q0", true));
	secondTransitions[3].add(State("q1"));
	secondTransitions[3].add(State("q2"));

	DeterminateFiniteAutomatonInt second(alphabet, secondStates, secondTransitions);
	cout << second;

	ofstream out("test.txt");
	out << first;

	return 0;
}
