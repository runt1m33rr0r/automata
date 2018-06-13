#include <iostream>
#include <exception>

#include "DeterminateFiniteAutomaton.h"

using namespace std;

int main()
{
	try
	{
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
			*dfa3 = *dfa1 | *dfa2;

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
		}
		
	}
	catch (const std::exception & e)
	{
		cout << e.what() << endl;
	}

	return 0;
}
