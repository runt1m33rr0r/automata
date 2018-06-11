#pragma once

#include "String.h"
#include "SmartArray.h"

class State
{
private:
	String name;
	bool isFinal;
	bool isStarting;

	SmartArray<State> compositeStates;
public:
	State();
	State(
		const String & name,
		bool isStarting = false, 
		bool isFinal = false, 
		const SmartArray<State> & compositeStates = SmartArray<State>());

	const String & getName() const;
	bool getFinal() const;
	bool getStarting() const;
	SmartArray<State> getCompositeStates() const;

	void setStarting(bool isStarting);
	void setFinal(bool isFinal);
};