#include <iostream>

using namespace std;

class String
{
private:
	char * value;

	void delete_value();
public:
	String();
	String(const char * value);
	String(const String & other);
	virtual ~String();

	String & operator=(const String & other);
};

ostream & operator<<(ostream & out, const String & other);
ostream & operator>>(ostream & out, const String & other);

int main()
{
	return 0;
}

void String::delete_value()
{
	if (this->value != nullptr)
	{
		delete[] this->value;
		this->value = nullptr;
	}
}

String::String() : value(nullptr)
{
}

String::String(const char * value)
{
}

String::String(const String & other)
{
}

String::~String()
{
}

String & String::operator=(const String & other)
{
	// TODO: insert return statement here
}

ostream & operator<<(ostream & out, const String & other)
{
	// TODO: insert return statement here
}

ostream & operator>>(ostream & out, const String & other)
{
	// TODO: insert return statement here
}
