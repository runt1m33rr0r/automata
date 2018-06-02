#pragma once

#include "String.h"

class State
{
private:
	String name;
	bool isFinal;
	bool isStarting;
public:
	State();
	State(const String & name, bool isFinal, bool isStarting);

	String getName() const;
	bool getFinal() const;
	bool getStarting() const;

	void setStarting(bool isStarting);
};