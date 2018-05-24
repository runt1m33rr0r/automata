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
	virtual ~SmartArray();

	SmartArray<T> & operator=(const SmartArray & other);
	T & operator[](size_t idx);

	size_t getCount() const;

	void add(const T element);
};

template<class T>
void SmartArray<T>::setElements(const T * elements, size_t count)
{
	this->deleteElements();

	this->count = count;
	for (size_t i = 0; i < count; i++)
	{
		this->elements[i] = elements[i];
	}
}

template<class T>
void SmartArray<T>::deleteElements()
{
	if (this->elements != nullptr)
	{
		delete[] this->elements;
	}
	this->count = 0;
}

template<class T>
SmartArray<T>::SmartArray() : elements(nullptr), count(0)
{
}

template<class T>
SmartArray<T>::SmartArray(const T * elems, size_t count) : elements(nullptr), count(count)
{
	this->setElements(elems, count);
}

template<class T>
SmartArray<T>::SmartArray(const SmartArray & other) : elements(nullptr), count(other.count)
{
	this->setElements(other.elements, other.count);
}

template<class T>
SmartArray<T>::~SmartArray()
{
	this->deleteElements();
}

template<class T>
SmartArray<T> & SmartArray<T>::operator=(const SmartArray & other)
{
	if (this != &other)
	{
		this->setElements(other.elements, other.count);
	}

	return *this;
}

template<class T>
T & SmartArray<T>::operator[](size_t idx)
{
	if (idx < this->count - 1 || idx > this->count - 1)
	{
		throw std::runtime_error("Index out of range!");
	}

	return this->elements[idx];
}

template<class T>
size_t SmartArray<T>::getCount() const
{
	return this->count;
}

template<class T>
void SmartArray<T>::add(const T element)
{
	size_t newCount = this->count + 1;
	T * newElements = new T[newCount];
	for (size_t i = 0; i < this->count; i++)
	{
		newElements[i] = this->elements[i];
	}
	newElements[newCount - 1] = element;

	this->deleteElements();

	this->count = newCount;
	this->elements = newElements;
}