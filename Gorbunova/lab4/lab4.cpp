#include "stdafx.h"
#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <iostream>

using namespace std;

	template <class Type>
	struct node
	{
		Type value;
		node* next;
		node* prev;

		node(const Type& value, node<Type>* next, node<Type>* prev)
			: value(value), next(next), prev(prev)
		{
		}
	};

	template <class Type>
	class list; //forward declaration

	template <class Type>
	class list_iterator
	{
	public:
		typedef ptrdiff_t difference_type;
		typedef Type value_type;
		typedef Type* pointer;
		typedef Type& reference;
		typedef size_t size_type;
		typedef std::forward_iterator_tag iterator_category;

		list_iterator()
			: m_node(NULL)
		{
		}

		list_iterator(const list_iterator& other)
			: m_node(other.m_node)
		{
		}

		node<Type>* getNode()
		{
			return m_node;
		}

		list_iterator& operator = (const list_iterator& other)
		{
			if (this != &other)
			{
				m_node = other.m_node;
			}
			return *this;
		}

		bool operator == (const list_iterator& other) const
		{
			return (m_node == other.m_node);
		}

		bool operator != (const list_iterator& other) const
		{
			return (m_node != other.m_node);
		}

		reference operator * ()
		{
			return m_node->value;
		}

		pointer operator -> ()
		{
			return &(m_node->value);
		}

		list_iterator& operator ++ ()
		{
			m_node = m_node->next;
			return *this;
		}

		list_iterator operator ++ (int)
		{
			list_iterator tmp(m_node);
			m_node = m_node->next;
			return tmp;
		}
	private:
		friend class list<Type>;

		list_iterator(node<Type>* p)
			: m_node(p)
		{
		}

		node<Type>* m_node;
	};

	template <class Type>
	class list
	{
	public:
		typedef Type value_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef list_iterator<Type> iterator;

		list()
			: m_head(nullptr), m_tail(nullptr)
		{
		}

		~list()
		{
			clear();
		}

		iterator begin()
		{
			return iterator(m_head);
		}

		iterator end()
		{
			return iterator(m_tail);
		}

		list(const list& other)
		{
			if (!other.empty())
			{
				node<value_type> *element = other.m_head;
				m_head = new node<value_type>(element->value, nullptr, nullptr);
				node<value_type> *m_element = m_head;
				node<value_type> *tmp = nullptr;
				while (element->next)
				{
					element = element->next;
					tmp = new node<value_type>(element->value, nullptr, m_element);
					m_element->next = tmp;
					m_element = tmp;
				}
				m_tail = tmp;
			}
			else
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
		}

		list(list&& other)
		{
			if (!other.empty())
			{
				node<value_type> *element = other.m_head;
				m_head = new node<value_type>(element->value, nullptr, nullptr);
				node<value_type> *m_element = m_head;
				node<value_type> *tmp = nullptr;
				while (element->next)
				{
					element = element->next;
					tmp = new node<value_type>(element->value, nullptr, m_element);
					m_element->next = tmp;
					m_element = tmp;
				}
				m_tail = tmp;
			}
			else
			{
				m_head = nullptr;
				m_tail = nullptr;
			}
			other.clear();
		}

		list& operator= (const list& other)
		{
			if (this != &other)
			{
				clear();
				if (!other.empty())
				{
					node<value_type> *element = other.m_head;
					m_head = new node<value_type>(element->value, nullptr, nullptr);
					node<value_type> *m_element = m_head;
					node<value_type> *tmp = nullptr;
					while (element->next)
					{
						element = element->next;
						tmp = new node<value_type>(element->value, nullptr, m_element);
						m_element->next = tmp;
						m_element = tmp;
					}
					m_tail = tmp;
				}
			}
			return *this;
		}

		void push_back(const value_type& value)
		{
			if (!empty())
			{
				node<value_type> *tmp = new node<value_type>(value, nullptr, m_tail);
				m_tail->next = tmp;
				m_tail = tmp;
			}
			else
			{
				m_head = new node<value_type>(value, nullptr, nullptr);
				m_tail = m_head;
			}
		}

		void push_front(const value_type& value)
		{
			if (!empty())
			{
				node<value_type> *tmp = new node<value_type>(value, m_head, nullptr);
				m_head->prev = tmp;
				m_head = tmp;
			}
			else
			{
				m_head = new node<value_type>(value, nullptr, nullptr);
				m_tail = m_head;
			}
		}
		//Ссылка по существу является псевдонимом для другого объекта. 
		//Поэтому в этом случае он не возвращает копию имени объекта или указателя на имя, 
		//а ссылку на само имя. Поэтому любые изменения в возвращаемом объекте непосредственно применяются к имени объекта.
		reference front()
		{
			if (m_head)
				return m_head->value;
		}

		const_reference front() const
		{
			if (m_head)
				return m_head->value;
		}

		reference back()
		{
			if (m_tail)
				return m_tail->value;
		}

		const_reference back() const
		{
			if (m_tail)
				return m_tail->value;
		}

		void pop_front()
		{
			if (!empty())
			{
				node<Type>* tmp = m_head->next;
				delete m_head;
				m_head = tmp;
				if (!empty())
					m_head->prev = nullptr;
			}
		}

		void pop_back()
		{
			if (!empty())
			{
				node<Type>* tmp = m_tail->prev;
				delete m_tail;
				m_tail = tmp;
				if (m_tail)
					m_tail->next = nullptr;
				else
					m_head = m_tail;
			}
		}

		void clear()
		{
			while (m_head)
				pop_front();
			m_tail = nullptr;
		}

		bool empty() const
		{
			if (m_head)
				return false;
			else
				return true;
		}

		size_t size() const
		{
			size_t count = 0;
			node<Type>* tmp = m_head;
			while (tmp)
			{
				count++;
				tmp = tmp->next;
			}
			return count;
		}
		
		void print()
		{
			node<Type>* tmp = m_head;
			while (tmp)
			{
				std::cout << tmp->value << " ";
				tmp = tmp->next;
			}
			std::cout << std::endl;
		}
		
		iterator insert(iterator pos, const Type& value)
		{
			iterator tmp(m_head);
			while (tmp != pos)
				tmp++;
			node <value_type> *elem = new node <Type>(value, tmp.getNode(), tmp.getNode()->prev);
			tmp.getNode()->prev = elem;
			tmp = elem->prev;
			if (tmp.getNode())
				tmp.getNode()->next = elem;
			while (m_head->prev)
				m_head = m_head->prev;
			return iterator(elem);
		}

		iterator erase(iterator pos)
		{
			iterator next_pos = pos.getNode()->next;
			node<Type> *f_free = pos.getNode();
			if (f_free == m_head)
			{
				m_head = m_head->next;
				m_head->prev = nullptr;
			}
			else
			{
				if (f_free == m_tail)
				{
					m_tail = m_tail->prev;
					m_tail->next = nullptr;
				}
				else
				{
					f_free->next->prev = f_free->prev;
					f_free->prev->next = f_free->next;
				}
			}
			delete[] f_free;
			return next_pos;
		}

	private:
		node<Type>* m_head;
		node<Type>* m_tail;
	};

int main()
{
	setlocale(LC_ALL, "Russian");
	list<int> l1;
	cout << "Вставка элемента 1 в конец" << endl;
	l1.push_back(1);
	cout << "Вставка элемента 0 в начало" << endl;
	l1.push_front(0);
	cout << "Вставка элементов 5,4 и 444 в конец" << endl;
	l1.push_back(5);
	l1.push_back(4);
	l1.push_back(444);
	l1.print();

	list<int> l;
	l = l1;
	
	cout << "Удаление последнего элемента" << endl;
	l1.pop_back();
	cout << "Удаление первого элемента" << endl;
	l1.pop_front();
	l1.print();

	cout << "Получим элемент из головы" << endl;
	cout << l1.front() << endl;
	cout << "Получим элемент из хвоста" << endl;
	cout << l1.back() << endl;

	cout << "Очистка" << endl;
	cout << "Проверка размера:" ;
	l1.clear();
	cout << l1.size() << endl;

	
	list_iterator<int> iterat = l.begin();
	cout << "Вставка элемента" << endl;
	l.insert(iterat, 100);
	l.print();

	iterat++;
	iterat++;

	cout << "Вставка элемента" << endl;
	l.insert(iterat, 200);

	l.print();

	cout << "Удаление элемента" << endl;
	iterat = l.erase(iterat);
	l.print();


    return 0;
}
