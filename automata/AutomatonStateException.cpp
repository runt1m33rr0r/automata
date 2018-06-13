#include "AutomatonStateException.h"

AutomatonStateException::AutomatonStateException(const String & missingState)
	: missingState(missingState), msg(nullptr)
{
	std::ostringstream convert;
	convert << "Error on line " << __LINE__ << ": " << "the state "
		<< this->missingState << " does not belong to this automaton!";

	this->msg = new char[strlen(convert.str().c_str()) + 1];
	strcpy_s(this->msg, strlen(convert.str().c_str()) + 1, convert.str().c_str());
}

AutomatonStateException::~AutomatonStateException()
{
	if (this->msg != nullptr)
	{
		delete[] this->msg;
		this->msg = nullptr;
	}
}

const char * AutomatonStateException::what() const
{
	return this->msg;
}
