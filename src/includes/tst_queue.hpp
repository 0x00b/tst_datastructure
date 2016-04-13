#ifndef _TST_QUEUE_H_
#define _TST_QUEUE_H_

#include "tst_list.hpp"

template<class T>
 class TstQueue
{
public:
	TstQueue()
	{
		list = new TstList<T>();
	}

	~TstQueue()
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

	T& front()
	{
		return *(list->begin());
	}
	void push(const T& t)
	{
		list->push_back(t);
	}
	bool empty()
	{
		return list->empty();
	}
	
	void pop()
	{
		list->pop_front();
	}
private:
	TstList<T> *list;
};

#endif
