#ifndef _TST_STACK_H_
#define _TST_STACK_H_
#include <iostream>
#include "tst_list.hpp"

template<class T>
class TstStack
{
public:
	TstStack()
	{
		list = new TstList<T>();
	}

	~TstStack()
	{
		if (list)
		{
			delete list;
		}
	}
	int size()
	{
		return list->size();
	}
	
	bool empty()
	{
		return list->empty();
	}
	void push(const T& t)
	{
		list->push_front(t);
	}
	void pop()
	{
		list->pop_front();
	}
	T& top()
	{
		return *(list->begin());
	}
private:
	TstList<T>* list;
};

#endif