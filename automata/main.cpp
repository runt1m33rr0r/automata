#include <iostream>
#include <exception>

#include "DeterminateFiniteAutomatonInt.h"

using namespace std;

int main()
{
	State test("test", false, false);
	cout << test.getName() << endl;

	DeterminateFiniteAutomatonInt automaton;

	return 0;
}
