#include "String.h"

void String::delete_value()
{
	if (this->value != nullptr)
	{
		delete[] this->value;
		this->value = nullptr;
	}
}

void String::set_value(const char * value)
{
	this->delete_value();

	const int len = strlen(value) + 1;
	this->value = new char[len];
	strcpy_s(this->value, len, value);
}

String::String() : value(nullptr)
{
	this->set_value("");
}

String::String(const char * value) : value(nullptr)
{
	this->set_value(value);
}

String::String(const String & other) : value(nullptr)
{
	this->set_value(other.value);
}

String::~String()
{
	this->delete_value();
}

String & String::operator=(const String & other)
{
	if (this != &other)
	{
		this->set_value(other.value);
	}

	return *this;
}

void String::export_data_to(std::ostream & out) const
{
	out << this->value;
}

void String::insert_data_from(std::istream & in)
{
	char buffer[BUFFER_SIZE] = "";
	in >> buffer;

	this->set_value(buffer);
}

std::ostream & operator<<(std::ostream & out, const String & other)
{
	other.export_data_to(out);
	return out;
}

std::istream & operator>>(std::istream & in, String & other)
{
	other.insert_data_from(in);
	return in;
}