#pragma once

#include "String.h"
#include "SmartArray.h"

class State
{
private:
	String name;
	bool isFinal;
	bool isStarting;

	SmartArray<State> innerStates;
public:
	State();
	State(
		const String & name,
		bool isStarting = false, 
		bool isFinal = false, 
		const SmartArray<State> & innerStates = SmartArray<State>());

	const String & getName() const;
	bool getFinal() const;
	bool getStarting() const;
	SmartArray<State> getInnerStates() const;

	void setStarting(bool isStarting);
	void setFinal(bool isFinal);

	bool operator==(const State & other) const;
};