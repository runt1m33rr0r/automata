#include <iostream>
#include <exception>

#include "DeterminateFiniteAutomaton.h"

using namespace std;

int main()
{
	try
	{
		/*SmartArray<char> alphabet;
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

		DeterminateFiniteAutomaton<char> first(alphabet, firstStates, firstTransitions);

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

		DeterminateFiniteAutomaton<char> second(alphabet, secondStates, secondTransitions);
		cout << second << endl << endl;

		DeterminateFiniteAutomaton<char> test = first & second;
		cout << test << endl << endl;

		ofstream out("test.txt");
		out << test;
		out.close();

		ifstream in("test.txt");
		unsigned alphabetType = 1;
		in >> alphabetType;
		in >> test;
		in.close();

		String word;
		cout << "word: ";
		cin >> word;
		cout << test.doesRecognizeWord(word) << endl << endl;*/

		unsigned automatonType;
		cout << "1 - int automaton" << endl << "2 - char automaton" << endl
			<< "automaton type: ";
		cin >> automatonType;

		if (automatonType == 1)
		{
			DeterminateFiniteAutomaton<int> * dfa1 = new DeterminateFiniteAutomaton<int>;
			cin >> *dfa1;
			cout << *dfa1 << endl;;

			DeterminateFiniteAutomaton<int> * dfa2 = new DeterminateFiniteAutomaton<int>;
			cin >> *dfa2;
			cout << *dfa2 << endl;;

			DeterminateFiniteAutomaton<int> * dfa3 = new DeterminateFiniteAutomaton<int>;
			*dfa3 = *dfa1 & *dfa2;

			ofstream out("test.txt");
			out << *dfa3;
			out.close();

			ifstream in("test.txt");
			unsigned alphabetType = 1;
			in >> alphabetType;
			if (alphabetType == 1)
			{
				in >> *dfa3;
			}
			cout << *dfa3 << endl << endl;

			cout << "give me some word to recognize: ";
			String word;
			cin >> word;
			cout << dfa3->doesRecognizeWord(word) << endl << endl;
		}
		else if (automatonType == 2)
		{
			DeterminateFiniteAutomaton<char> * dfa1 = new DeterminateFiniteAutomaton<char>;
			cin >> *dfa1;
			cout << *dfa1 << endl;

			DeterminateFiniteAutomaton<char> * dfa2 = new DeterminateFiniteAutomaton<char>;
			cin >> *dfa2;
			cout << *dfa2 << endl;

			DeterminateFiniteAutomaton<char> * dfa3 = new DeterminateFiniteAutomaton<char>;
			*dfa3 = *dfa1 & *dfa2;

			ofstream out("test.txt");
			out << *dfa3;
			out.close();

			ifstream in("test.txt");
			unsigned alphabetType = 2;
			in >> alphabetType;
			if (alphabetType == 2)
			{
				in >> *dfa3;
			}
			cout << *dfa3 << endl << endl;

			cout << "give me some word to recognize: ";
			String word;
			cin >> word;
			cout << dfa3->doesRecognizeWord(word) << endl << endl;
		}
	}
	catch (const std::exception & e)
	{
		cout << e.what() << endl;
	}

	return 0;
}