#pragma once

#define BUFFER_SIZE 1000000

#include <iostream>

class String
{
private:
	char * value;

	void delete_value();
	void set_value(const char * value);
public:
	String();
	String(const char * value);
	String(const String & other);
	virtual ~String();

	String & operator=(const String & other);

	void export_data_to(std::ostream & out) const;
	void insert_data_from(std::istream & in);
};

std::ostream & operator<<(std::ostream & out, const String & other);
std::istream & operator>>(std::istream & in, String & other);