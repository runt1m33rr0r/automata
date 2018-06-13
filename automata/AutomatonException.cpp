#include "AutomatonException.h"

AutomatonException::AutomatonException(
	const String & tryStateName, 
	const String & oldStateName, 
	unsigned line) : 
	tryStateName(tryStateName), oldStateName(oldStateName), line(line)
{
	std::ostringstream convert;
	convert << "Error on line " << this->line << ": " << "automaton already has starting state "
		<< this->oldStateName << " and you can not set " << tryStateName << " as starting!";

	this->msg = new char[strlen(convert.str().c_str()) + 1];
	strcpy_s(this->msg, strlen(convert.str().c_str()) + 1, convert.str().c_str());
}

AutomatonException::~AutomatonException()
{
	if (this->msg != nullptr)
	{
		delete[] this->msg;
		this->msg = nullptr;
	}
}

const char * AutomatonException::what() const
{
	return this->msg;
}
