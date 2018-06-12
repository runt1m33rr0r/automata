#ifndef SMART_ARRAY
#define SMART_ARRAY

template <class T> class SmartArray
{
private:
	T * elements;
	size_t count;

	void setElements(const T * elements, size_t count)
	{
		this->deleteElements();

		this->count = count;
		this->elements = new T[count];
		for (size_t i = 0; i < count; i++)
		{
			this->elements[i] = elements[i];
		}
	}

	void deleteElements()
	{
		if (this->elements != nullptr)
		{
			delete[] this->elements;
			this->elements = nullptr;
		}
		this->count = 0;
	}

	void checkIndex(size_t idx) const
	{
		if (this->count == 0 || idx + 1 > this->count)
		{
			throw std::runtime_error("Index out of range!");
		}
	}
public:
	SmartArray() : elements(nullptr), count(0)
	{
	}

	SmartArray(const T * elems, size_t count) : elements(nullptr), count(count)
	{
		this->setElements(elems, count);
	}

	SmartArray(const SmartArray & other) : elements(nullptr), count(other.count)
	{
		this->setElements(other.elements, other.count);
	}

	virtual ~SmartArray()
	{
		this->deleteElements();
	}

	SmartArray<T> & operator=(const SmartArray & other)
	{
		if (this != &other)
		{
			this->setElements(other.elements, other.count);
		}

		return *this;
	}

	T & operator[](size_t idx)
	{
		this->checkIndex(idx);
		return this->elements[idx];
	}

	const T & operator[](size_t idx) const
	{
		this->checkIndex(idx);
		return this->elements[idx];
	}

	size_t getCount() const
	{
		return this->count;
	}

	int indexOf(const T & obj) const
	{
		for (size_t i = 0; i < this->count; i++)
		{
			if (this->elements[i] == obj)
			{
				return i;
			}
		}

		return -1;
	}

	void add(const T element)
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
};

#endif