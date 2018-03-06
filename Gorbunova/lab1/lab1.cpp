#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>

template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
	}
    	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);
		return m_array[index];
	}

// (copy) constructor
	Array(const Array &obj)
		: m_size(obj.size())
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		if(m_size)
			std::copy(obj.m_array.get(), obj.m_array.get()+obj.size(), m_array.get());
	}
  // (move) constructor
	Array(Array &&obj)
	    : m_size(0)
	{
		m_array.reset(obj.m_array.release());//функция-член обнуления битов
		m_size = obj.m_size;
		obj.m_size = 0;
	}
   // (assignment) operator
	Array &operator=(Array obj)
	{
		std::swap(m_size, obj.m_size);
		std::swap(m_array, obj.m_array);
		return *this;	
	}

private:
	size_t m_size;
	std::unique_ptr<T[]> m_array;
};
