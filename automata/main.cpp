#include <iostream>
#include <exception>

#include "State.h"
#include "SmartArray.h"

using namespace std;

int main()
{
	State test("test");
	cout << test.getName() << endl;

	return 0;
}