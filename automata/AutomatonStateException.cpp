#include "AutomatonStateException.h"

AutomatonStateException::AutomatonStateException(const String & missingState, unsigned line)
	: missingState(missingState), msg(nullptr), line(line)
{
	std::ostringstream convert;
	convert << "Error on line " << this->line << ": " << "the state "
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
