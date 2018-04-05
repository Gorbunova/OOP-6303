#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
using namespace std;

template <typename Type>
class vector
{
public:
	typedef Type* iterator;
	typedef const Type* const_iterator;

	typedef Type value_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef std::ptrdiff_t difference_type;
	//конструкторы для разных форм инициализации    
	// определяет пустой начальный вектор
	explicit vector(size_t count = 0) //запрещает автоматическое создание конвертирующего конструктора (явный констр-р)
		: m_first(count ? new Type[count]() : nullptr)
		, m_last(count ? (m_first + count) : nullptr)
	{
		cout << "Конструктор пустого вектора" << endl;
	}
	// конструктор копирует диапазон [First, Last) вектора
	template <typename InputIterator>
	vector(InputIterator first, InputIterator last)
		: m_first((last - first) ? new Type[last - first]() : nullptr)
		, m_last((last - first) ? (m_first + (last - first)) : nullptr)
	{
		cout << "Конструктор копирования диапазона" << endl;
		std::copy(first, last, m_first);
	}
	//инициализация списком элементов
	vector(std::initializer_list<Type> init)
		: m_first(init.size() ? new Type[init.size()]() : nullptr)
		, m_last(init.size() ? (m_first + init.size()) : nullptr)
	{
		cout << "Конструктор инициализация списком" << endl;
		std::copy(init.begin(), init.end(), m_first);
	}

	vector(const vector& other)//копирования
		: m_first(other.size() ? new Type[other.size()]() : nullptr)
		, m_last(other.size() ? (m_first + other.size()) : nullptr)
	{
		cout << "Конструктор копирования" << endl;
		std::copy(other.begin(), other.end(), m_first);
	}

	vector(vector&& other)//перемещения
		:m_first(other.m_first)
		, m_last(other.m_last)
	{
		cout << "Конструктор перемещения" << endl;
		other.m_first = nullptr;
		other.m_last = nullptr;
	}

	~vector()
	{
		if (!empty())
			delete[] m_first;
		cout << "Деструктор" << endl;
	}


	//assignment operators
	vector& operator=(const vector& other)
	{
		cout << "Оператор 1" << endl;
		if (this != &other)
		{
			if (!empty())
				delete[] m_first;
			m_first = nullptr;
			m_last = nullptr;
			if (other.size() > 0)
			{
				m_first = new Type[other.size()];
				m_last = m_first + other.size();
				std::copy(other.begin(), other.end(), m_first);
			}
		}
		return *this;
	}

	vector& operator=(vector&& other)
	{
		cout << "Оператор 2" << endl;
		if (this != &other)
		{
			if (!empty())
				delete[] m_first;
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}
		return *this;
	}

	// assign method
	//Задаёт значения в контейнере 
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		cout << "Assign "<< endl;
		if (m_first)
		{
			delete[]m_first;
			m_first = nullptr;
			m_last = nullptr;
		}
		if (last - first > 0)
		{
			m_first = new Type[last - first];
			m_last = m_first + (last - first);
			std::copy(first, last, m_first);
		}
	}

	// resize methods
	//Изменяет количество хранимых элементов
	void resize(size_t count)
	{
		cout << "Resize" << endl;
		if (count != 0)
		{
			int difference = count - (m_last - m_first);
			if (difference > 0)
			{
				iterator tmp = new Type[count];
				std::copy(m_first, m_last, tmp);
				if (m_first)
					delete[] m_first;
				m_first = tmp;
				m_last = m_first + count;
			}
			else m_last = m_last + difference;
		}
		else
		{
			m_last = m_first;
			delete[] m_first;
		}
	}

	//erase methods
	//Удаляет элементы 
	iterator erase(const_iterator pos)
	{
		cout << "Erase" << endl;
		//вызов исключения в случае попытки доступа к элементу по индексу, который не существует в классе Vector
		if ((pos < m_first) || pos >= m_last)
			throw std::out_of_range("Pos is out of range");
		size_t delta = pos - m_first;//смещение
		std::rotate(m_first + delta, m_first + delta + 1, m_last);
		resize(m_last - m_first - 1);
		return m_first + delta;
	}

	iterator erase(const_iterator first, const_iterator last)
	{
		cout << "Erase diapason" << endl;
		if ((first < m_first) || (first > m_last) || (last < m_first) || (last > m_last))
			throw std::out_of_range("out of range");
		size_t delta = first - m_first;
		size_t length = last - first;
		std::rotate(m_first + delta, m_first + delta + length, m_last);
		resize(m_last - m_first - length);
		return m_first + delta;
	}

	//insert methods
	//Вставляет элементы. 
	iterator insert(const_iterator pos, const Type& value)
	{
		cout << "Insert " << endl;
		size_t delta = pos - m_first;
		push_back(value);
		std::rotate(m_first + delta, m_last - 1, m_last);
		return m_first + delta;
	}
	
	template <typename InputIterator>
	iterator insert(const_iterator pos, InputIterator first, InputIterator last)
	{
		cout << "Insert diapason" << endl;
		size_t delta = pos - m_first;
		size_t length = last - first;
		size_t _size = size();
		iterator tmp = new Type[_size + length];
		std::copy(m_first, m_last, tmp);
		std::copy(first, last, tmp + _size);
		std::rotate(tmp + delta, tmp + _size, tmp + _size + length);
		if (m_first)
			delete[] m_first;
		m_first = tmp;
		m_last = tmp + _size + length;
		return m_first + delta;
	}

	//push_back methods
	//Добавляет элемент в конец 
	void push_back(const value_type& value)
	{
		cout << "Push back" << endl;
		size_t _size = size();
		iterator tmp = new Type[_size + 1];
		std::copy(m_first, m_last, tmp);
		if (m_first)
			delete[] m_first;
		m_first = tmp;
		m_last = m_first + _size + 1;
		*(m_last - 1) = value;
	}

	//at methods
	reference at(size_t pos)
	{
		return checkIndexAndGet(pos);
	}

	const_reference at(size_t pos) const
	{
		return checkIndexAndGet(pos);
	}

	//[] operators
	reference operator[](size_t pos)
	{
		return m_first[pos];
	}

	const_reference operator[](size_t pos) const
	{
		return m_first[pos];
	}

	//*begin methods
	iterator begin()
	{
		return m_first;
	}

	const_iterator begin() const
	{
		return m_first;
	}

	//*end methods
	iterator end()
	{
		return m_last;
	}

	const_iterator end() const
	{
		return m_last;
	}

	//size method
	size_t size() const
	{
		return m_last - m_first;
	}

	//empty method
	bool empty() const
	{
		return m_first == m_last;
	}

private:
	reference checkIndexAndGet(size_t pos) const
	{
		if (pos >= size())
		{
			throw std::out_of_range("out of range");
		}

		return m_first[pos];
	}

	//your private functions

private:
	iterator m_first;
	iterator m_last;
};
