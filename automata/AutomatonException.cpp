#include "AutomatonException.h"

AutomatonException::AutomatonException(const String & tryStateName, const String & oldStateName) : 
	tryStateName(tryStateName), oldStateName(oldStateName)
{
	std::ostringstream convert;
	convert << "Error on line " << __LINE__ << ": " << "automaton already has starting state "
		<< this->oldStateName << " and you can not set " << tryStateName << " as starting!";

	this->msg = new char[strlen(convert.str().c_str()) + 1];
	strcpy_s(this->msg, strlen(convert.str().c_str()) + 1, convert.str().c_str());
}

AutomatonException::~AutomatonException()
{
	delete[] this->msg;
}

const char * AutomatonException::what() const
{
	return this->msg;
}
