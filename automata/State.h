#pragma once

#include "String.h"

class State
{
private:
	String name;
public:
	State();
	State(const String & name);

	String getName() const;
};