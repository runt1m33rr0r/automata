#include "String.h"

void String::deleteValue()
{
	if (this->value != nullptr)
	{
		delete[] this->value;
		this->value = nullptr;
	}
}

void String::setValue(const char * value)
{
	this->deleteValue();

	const int len = strlen(value) + 1;
	this->value = new char[len];
	strcpy_s(this->value, len, value);
}

String::String() : value(nullptr)
{
	this->setValue("");
}

String::String(const char * value) : value(nullptr)
{
	this->setValue(value);
}

String::String(const String & other) : value(nullptr)
{
	this->setValue(other.value);
}

String::~String()
{
	this->deleteValue();
}

String & String::operator=(const String & other)
{
	if (this != &other)
	{
		this->setValue(other.value);
	}

	return *this;
}

bool String::operator==(const String & other) const
{
	if (this == &other || this->value == other.value)
	{
		return true;
	}

	return false;
}

void String::exportDataTo(std::ostream & out) const
{
	out << this->value;
}

void String::insertDataFrom(std::istream & in)
{
	char buffer[BUFFER_SIZE] = "";
	in >> buffer;

	this->setValue(buffer);
}

std::ostream & operator<<(std::ostream & out, const String & other)
{
	other.exportDataTo(out);
	return out;
}

std::istream & operator>>(std::istream & in, String & other)
{
	other.insertDataFrom(in);
	return in;
}