#ifndef AUTOMATON_STATE_EXCEPTION
#define AUTOMATON_STATE_EXCEPTION

#include <exception>
#include <sstream>

#include "String.h"
#include "State.h"

class AutomatonStateException : public std::exception
{
private:
	String missingState;
	char * msg;
	unsigned line;
public:
	AutomatonStateException(const String & missingState, unsigned line);
	~AutomatonStateException();

	const char * what() const;
};

#endif