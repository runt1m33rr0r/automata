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
	State(const String & name, bool isStarting = false, bool isFinal = false);

	const String & getName() const;
	bool getFinal() const;
	bool getStarting() const;

	void setStarting(bool isStarting);
	void setFinal(bool isFinal);
};