#pragma once

template <class T> class SmartArray
{
private:
	T * elements;
	size_t count;

	void setElements(const T * elements, size_t count);
	void deleteElements();
public:
	SmartArray();
	SmartArray(const T * elems, size_t count);
	SmartArray(const SmartArray & other);
	~SmartArray();

	SmartArray<T> & operator=(const SmartArray & other);
	T & operator[](size_t idx);

	size_t getCount() const;

	void add(const T element);
};