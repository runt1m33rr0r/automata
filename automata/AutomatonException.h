#ifndef AUTOMATON_EXCEPTION
#define AUTOMATON_EXCEPTION

#include <exception>
#include <sstream>

#include "String.h"

class AutomatonException : public std::exception
{
private:
	String oldStateName;
	String tryStateName;
	char * msg;
public:
	AutomatonException(const String & tryStateName, const String & oldStateName);
	~AutomatonException();

	const char * what() const;
};

#endif