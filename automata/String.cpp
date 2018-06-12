#include "String.h"
#include "SmartArray.h"

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

void String::checkIndex(size_t idx) const
{
	if (this->getLen() == 0 || idx + 1 > this->getLen())
	{
		throw std::runtime_error("Index out of range!");
	}
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
	if (this == &other)
	{
		return true;
	}

	bool areEqual = strcmp(this->value, other.value) == 0 ? true : false;
	return areEqual;
}

String String::operator+(const String & other) const
{
	unsigned thisLen = strlen(this->value);
	unsigned otherLen = strlen(other.value);
	unsigned newLen = thisLen + otherLen + 1;
	char * buffer = new char[newLen];

	strcpy_s(buffer, newLen, this->value);
	strcat_s(buffer, newLen, other.value);

	String newString(buffer);
	delete[] buffer;

	return newString;
}

char & String::operator[](size_t idx)
{
	this->checkIndex(idx);
	return this->value[idx];
}

const char & String::operator[](size_t idx) const
{
	this->checkIndex(idx);
	return this->value[idx];
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

size_t String::getLen() const
{
	return strlen(this->value);
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