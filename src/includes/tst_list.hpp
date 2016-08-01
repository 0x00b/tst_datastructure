#ifndef _TST_LIST_H_
#define _TST_LIST_H_

#include "tst_construct.hpp"

//#include <iterator>

template<class T>
struct TstListNode
{
	TstListNode* next;
	TstListNode* prev;
	T data;
};

template<class T> struct TstListIterator;

template<class T>
struct TstListIterator //:public std::iterator<std::forward_iterator_tag,T>
{
	//
	typedef T value_type;	//迭代器所指的类型
	typedef T* pointer;		//迭代器所指的类型的指针类型
	typedef T& refrence;	//迭代器所指的类型的引用类型
							//	typedef  iterator_category;	//迭代器的类型
							//	typedef int difference_type;	//迭代器直接的距离 int arr[] ; arr + 1 == a[1];

	typedef const T* const_pointer;
	typedef const T& const_refrence;

	typedef TstListIterator<T> iterator;
	typedef TstListNode<T>* linktype;

	linktype node;

	TstListIterator()
	{
	}

	TstListIterator(linktype n) :node(n)
	{
	}

	TstListIterator(const TstListIterator<T>& it) :node(it.node)
	{
	}

	~TstListIterator()
	{
	}

	iterator& operator=(const iterator& it)
	{
		this->node = it.node;
		return *this;
	}

	bool operator==(const iterator& it)const
	{
		return it.node == this->node;
	}
	bool operator!=(const iterator& it)const
	{
		return it.node != this->node;
	}

	T& operator*()const
	{
		return node->data;
	}

	/*
	* 在迭代器中，前置++和后置++的区别就体现出来了
	*/
	iterator& operator++()
	{
		node = (linktype)(node->next);
		return *this;
	}
	//後置++
	iterator operator++(int)
	{
		iterator temp = *this;
		++*this;
		return temp;
	}
	iterator& operator--()
	{
		node = (linktype)(node->prev);
		return *this;
	}
	//後置--
	iterator operator--(int)
	{
		iterator temp = *this;
		--*this;
		return temp;
	}

};

template<class T>
class TstList
{
public:
	typedef TstListIterator<T> iterator;
	typedef TstListNode<T>* linktype;

	TstList() :lenth(0)
	{
		head = GetNode();
		head->next = head;
		head->prev = head;
	}
	~TstList()
	{
		clear();
		erase(head);
	}

	inline int size()const
	{
		return lenth;
	}
	inline bool empty()const
	{
		return (0 == lenth);
	}

	iterator begin()
	{
		return (linktype)(head->next);
	}

	iterator end()
	{
		return head;
	}

	iterator insert(iterator pos, const T& t)
	{
		linktype temp = GetNode();

		/*
		* 构造data
		*/
		TstConstruct(&temp->data, t);

		temp->next = pos.node;
		temp->prev = (pos.node)->prev;
		(linktype((pos.node)->prev))->next = temp;
		(pos.node)->prev = temp;
		++lenth;
		return temp;
	}
	void erase(iterator pos)
	{
		((linktype)(pos.node)->prev)->next = (pos.node)->next;
		((linktype)((pos.node)->next))->prev = (pos.node)->prev;

		/*:
		* 对node->data 做相应的释放动作
		*/
		TstDestroy(&(*pos));

		//delete pos.node;
		free(pos.node);
		--lenth;
	}

	iterator push_front(const T& t)
	{
		return insert(begin(), t);
	}

	iterator push_back(const T& t)
	{
		return insert(end(), t);
	}

	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}
	void clear()
	{
		iterator next;
		iterator it = begin();
		for (; it != end(); it = next)
		{
			next = (linktype)(it.node)->next;
			erase(it);
		}
	}
private:
	int lenth;

	TstListNode<T>* head; /* 链表的头结点。 */

	TstListNode<T>* GetNode()  /* 用来获得一个节点。 */
	{
		TstListNode<T>* temp = (TstListNode<T>*)malloc(sizeof(TstListNode<T>));
		if (NULL == temp)
		{
			//throw ...
		}
		memset(temp, 0x00, sizeof(TstListNode<T>));
		return temp;
	}
};

#endif
