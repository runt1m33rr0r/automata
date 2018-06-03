#pragma once

#define BUFFER_SIZE 1000000

#include <iostream>

class String
{
private:
	char * value;

	void deleteValue();
	void setValue(const char * value);
public:
	String();
	String(const char * value);
	String(const String & other);
	virtual ~String();

	String & operator=(const String & other);
	bool operator==(const String & other) const;

	void exportDataTo(std::ostream & out) const;
	void insertDataFrom(std::istream & in);
};

std::ostream & operator<<(std::ostream & out, const String & other);
std::istream & operator>>(std::istream & in, String & other);