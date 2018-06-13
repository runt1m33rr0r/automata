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
	unsigned line;
public:
	AutomatonException(const String & tryStateName, const String & oldStateName, unsigned line);
	~AutomatonException();

	const char * what() const;
};

#endif