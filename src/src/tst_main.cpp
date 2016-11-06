#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <list>
#include "tst_tree.hpp"
#include "tst_queue.hpp"
#include "tst_list.hpp"
#include "tst_stack.hpp"
#include "tst_graphic.hpp"

#if defined(_WIN32) || defined(_WIN64)
	#define _WIN
	#define _CRTDBG_MAP_ALLOC
	#include <windows.h>
	#include <crtdbg.h>
	#include <time.h>
#else
	#include <sys/time.h>

#endif

extern "C" {
	#include "tst_rbtree.h"
	#include "tst_avltree.h"
}
using namespace std;

#define len 12

int Now();
void tst_stack_main();
void tst_avl_main();
void tst_rbt_main();
void tst_ghc_main();
void tst_leak_main();

int main(int argc, char* args[])
{
#if 1
	tst_stack_main();
#elif 0
	tst_rbt_main();
#elif 0
	tst_rbt_main();
#elif 1
	tst_ghc_main();

#endif

	/* 内存泄漏测试 */
#if 0
	tst_leak_main();
#endif

#if defined(_WIN)
	_CrtDumpMemoryLeaks();
#else

#endif


#if defined(_WIN32) || defined(_WIN64)
	return system("pause");
#else
	return 0;
#endif
}

struct LeakTest
{
	int* data;
	LeakTest(int i)
	{
		data = new int(i);
	}
	LeakTest(const LeakTest& lt)
	{
		data = new int(*lt.data);
}
	~LeakTest()
	{
		delete data;
	}
};
int Now()
{
#if defined(_WIN)
	return GetTickCount();
#else
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	return tv.tv_usec;
#endif
}
void tst_leak_main() 
{
	//list<LeakTest> otll; list<LeakTest>::iterator oit;
	TstList<LeakTest> otll; TstList<LeakTest>::iterator oit;
	
	int str = Now();
	for (size_t i = 0; i < 10000; ++i)
	{
		LeakTest olt(i);
		otll.insert(otll.begin(), olt);
	}
	printf("time: %d \n", Now() - str);

	oit = otll.begin();
	for (; oit != otll.end(); ++oit)
	{
		cout << *(*oit).data << " " ;
	}
	cout << endl;

	/*   */
	TstList<LeakTest*> ptll;
	LeakTest plt1(2);
	LeakTest plt2(22);
	LeakTest plt3(222);
	ptll.insert(ptll.begin(), &plt1);
	ptll.insert(ptll.begin(), &plt2);
	ptll.insert(ptll.begin(), &plt3);
	TstList<LeakTest*>::iterator pit = ptll.begin();
	for (; pit != ptll.end(); ++pit)
	{
		cout << *(*pit)->data << " ";
	}
	cout << endl;

	/*   */
	TstList<int> oint;
	int  n;
	oint.insert(oint.begin(), n);

	/*   */
	TstList<double*> pint;
	double*  pn = new double(99);
	pint.insert(pint.begin(), pn);
	delete pn;

}

///////////////////////////////////
/*
 * 把公式字符串拆分成单个元素，放在队列中
 */
bool split_formula(char* str, TstList<string>& lst)
{
	assert(str != NULL);

	string temp("");

	while (*str != 0)
	{
		if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '(' || *str == ')' )
		{
			temp = *str++;
			lst.push_back(temp);
		}
		else if ('0' <= *str && *str <= '9')
		{
			while (*str != 0 && '0' <= *str && *str <= '9')
			{
				temp += *str++;
			}
			lst.push_back(temp);
		}
		else if (*str == ' ')
		{
			str++;
		}
		else
		{
			return false;
		}
		temp.clear();
	}
	return true;
}

/*
 * 判断串是数字
 */
bool is_number(string& str)
{
	if (!str.empty())
	{
		for (string::iterator it = str.begin(); it != str.end(); ++it)
		{
			if ((*it) < '0' || (*it) > '9')
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

/*
 * 判断一个表达式是正确的，例如：3*（23+2）是正确的，但是3（23+2）是错误的。
 */
bool is_right_formula(TstList<string>& lst)
{
	return true;
}
/* 
 * 中缀表达式转后缀表达式
 * 
 * 1、数字直接输出到后序表达式队列。
 * 2、遇到 "+","-" ，则先弹出符号栈中的元素，弹出一个元素则需要把这个元素放进后序表达式队列，出栈时遇到 "(" 或者栈空为止，然后把当前的符号放进符号栈。
 * 3、遇到 "*","/","("，则直接压进符号栈。
 * 4、遇到 ")"， 则需要弹出符号栈中的元素，直到找到与之对应的前面的"("为止。
 * 5、当中序表达式队列中没有元素时，一次弹出符号栈中的元素，同时放进后续表达式队列中。
 */
bool mid_to_aft(TstList<string>& lst_mid_formula, TstList<string>& lst_aft_formula)
{
	TstStack<string> stk_formula;

	if (!is_right_formula(lst_mid_formula))
	{
		return false;
	}
	for (TstList<string>::iterator it = lst_mid_formula.begin(); it != lst_mid_formula.end(); ++it)
	{
		string& str = *it;

		if (is_number(str))
		{
			lst_aft_formula.push_back(str);
		}
		else if ('+' == str[0] || '-' == str[0])
		{
			while (!stk_formula.empty())
			{
				string& str_top = stk_formula.top();
				if (str_top[0] != '(')
				{
					lst_aft_formula.push_back(str_top);
					stk_formula.pop();
				}
				else
				{
					break;
				}
			}

			stk_formula.push(str);
		}
		else if ('*' == str[0] || '/' == str[0])
		{
			stk_formula.push(str);
		}
		else if ('(' == str[0])
		{
			stk_formula.push(str);
		}
		else if (')' == str[0])
		{
			string str_top("");
			while ((str_top = stk_formula.top())[0] != '(')
			{
				stk_formula.pop();
				lst_aft_formula.push_back(str_top);
			}
			stk_formula.pop();
		}
	}
	while (!stk_formula.empty())
	{
		lst_aft_formula.push_back(stk_formula.top());
		stk_formula.pop();
	}
	return true;
}
/*
 * 栈的应用，中缀表达式，后缀表达式
 *
 */
void tst_stack_main() 
{
	char str_formula[100];
	TstList<string> lst_mid_formula; /* 中缀表达式*/
	TstList<string> lst_aft_formula; /* 后缀表达式*/
	cout << "input math formula:" << endl;
	cin>>str_formula;

	/* 拆分出表达式的各元素，按照原来的顺序放在队列中 */
	bool bret = split_formula(str_formula, lst_mid_formula);
	if (bret)
	{
		cout << "中缀表达式：";
		for (TstList<string>::iterator it = lst_mid_formula.begin(); it != lst_mid_formula.end(); ++it)
		{
			string& str = *it;
			cout << str.c_str() << " ";
		}
		/* 调用函数*/
		/* 转化为后缀表达式 ，事实上，通过中缀和后缀表达式可以还原二叉树*/
		mid_to_aft(lst_mid_formula, lst_aft_formula);

		cout << "\n后缀表达式：";
		for (TstList<string>::iterator it = lst_aft_formula.begin(); it != lst_aft_formula.end(); ++it)
		{
			cout << (*it).c_str() << " ";
		}
		cout << endl;
	}
}


void tst_avl_main()
{
	tst_avlnode* root = NULL;

	//tst_avl_node_init(root, 0);

	tst_avlnode* node[len];


	for (int i = 0; i < len; i++)
	{
		node[i] = (tst_avlnode*)malloc(sizeof(tst_avlnode));
		tst_avl_node_init(node[i], i);
		tst_avl_insert(&root, node[i]); dspavltree(root); printf("\n");
	}
#if 0
	// test tst_avl_rotate_left
	root = node[2];
	root->height = 4;

	root->lchild = node[1];
	node[1]->parent = root;
	root->lchild->height = 1;

	root->rchild = node[4];
	node[4]->parent = root;
	root->rchild->height = 3;

	root->rchild->lchild = node[3];
	node[3]->parent = root->rchild;
	root->rchild->lchild->height = 1;

	root->rchild->rchild = node[5];
	node[5]->parent = root->rchild;
	root->rchild->rchild->height = 2;

	root->rchild->rchild->rchild = node[6];
	node[6]->parent = root->rchild->rchild;
	root->rchild->rchild->rchild->height = 1;

	dspavltree(root); printf("\n");
	tst_avl_rotate_left(&root);
	dspavltree(root); printf("\n");

	// test tst_avl_rotate_left

	tst_avl_rotate_right(&root);
	dspavltree(root); printf("\n");

#endif

#if 0
	// test tst_avl_delete
	root = node[2];
	root->height = 4;

	root->lchild = node[1];
	node[1]->parent = root;
	root->lchild->height = 1;

	root->rchild = node[4];
	node[4]->parent = root;
	root->rchild->height = 3;

	root->rchild->lchild = node[3];
	node[3]->parent = root->rchild;
	root->rchild->lchild->height = 1;

	root->rchild->rchild = node[5];
	node[5]->parent = root->rchild;
	root->rchild->rchild->height = 2;

	root->rchild->rchild->rchild = node[6];
	node[6]->parent = root->rchild->rchild;
	root->rchild->rchild->rchild->height = 1;

	dspavltree(root); printf("\n");

#elif 0
	printf("delete:3 5 2 6 9\n");
	tst_avl_delete(&root, node[3]);
	free(node[3]);

	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[5]);
	free(node[5]);
	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[2]);
	free(node[2]);
	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[6]);
	free(node[6]);
	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[9]);
	free(node[9]);
	dspavltree(root); printf("\n");
#else 

	printf("delete:\n");
	for (int i = len - 1; i >0; i--)
	{
		printf("del[%d]\n", i);
		//tst_avl_delete_beta(&root, node[i]);
		tst_avl_delete(&root, node[i]);
		free(node[i]);
		dspavltree(root); printf("\n");
	}
#endif

	destoytree(root, NULL);

}
void tst_rbt_main()
{
	/*	queue<tst_rbtnode*> q; */

#if 1
	tst_rbtree t;
	tst_rbtnode sen;
	tst_rbtnode* node[len];

	tst_rbt_node_init(&sen, 0);

	tst_rbt_init(&t, &sen, tst_rbt_insert_default);

	for (int i = 0; i < len; i++)
	{
		node[i] = (tst_rbtnode*)malloc(sizeof(tst_rbtnode));
		tst_rbt_node_init(node[i], i + 1);
		tst_rbt_insert(&t, node[i]);
		dsprbttree(t.root, t.sentinel); printf("\n");
	}
	/* 显示树 */

	printf("tree node count:%d  tree height:%d\n", \
		treenodecount(t.root, t.sentinel), treehigh(t.root, t.sentinel));
	printf("tree:\n");
	dsprbttree(t.root, t.sentinel); printf("\n");

#if 1
	printf("predg:");
	predsptree(t.root, t.sentinel);
	printf("\n");
	printf("pres1:");
	predsptree_s_1(t.root, t.sentinel);
	printf("\n");
	printf("pres2:");
	predsptree_s_2(t.root, t.sentinel);
	printf("\n\n");

	printf("middg:");
	middsptree(t.root, t.sentinel);
	printf("\n");
	printf("mids1:");
	middsptree_s_1(t.root, t.sentinel);
	printf("\n");
	printf("rmid:");
	middsptree_s_s(t.root, t.sentinel);
	printf("\n\n");

	printf("aftdg:");
	aftdsptree(t.root, t.sentinel);
	printf("\n");
	printf("afts1:");
	aftdsptree_s_1(t.root, t.sentinel);
	printf("\n");

#endif
	tst_rbtnode* p;
	/* 删除节点 */
#if 1
	p = tst_rbt_find(&t, t.sentinel, 8);
	printf("\n del find = %d:\n", p ? p->key : -1);
	/*
	p = tst_rbt_min_node(t.root->rchild, t.sentinel);
	printf("min=%d\n", p ? p->key : -1);
	*/
	tst_rbt_delete(&t, p);
	free(p);
	dsprbttree(t.root, t.sentinel); printf("\n");
	printf("\n");
#endif

#if 0
	printf("mirror:\n");
	mirror(t.root, t.sentinel);
	dsprbttree(t.root, t.sentinel); printf("\n");
#endif

#if 0
	printf("\n转换成双向循环链表:\n");
	tst_rbtnode* ph = changetolink(t.root, t.sentinel);

	printf("正向:");
	p = ph->lchild;
	while (p != ph)
	{
		printf("%d ", p->key);
		p = p->lchild;
	}
	printf("\n反向:");
	p = ph->parent;
	while (p != ph)
	{
		printf("%d ", p->key);
		p = p->parent;
	}

	/* 释放 */
	tst_rbtnode* pt;
	p = ph->lchild;
	while (p != ph)
	{
		pt = p;
		p = p->lchild;
		free(pt);
	}
	//	free(ph);
#else
	destoytree(t.root, t.sentinel);
#endif

#if 1
	tst_rbtnode n[7];
	n[0].key = 0;
	n[1].key = 1;
	n[2].key = 1;
	n[3].key = 2;
	n[4].key = 3;
	n[5].key = 3;
	n[6].key = 2;

	n[0].lchild = &n[1];
	n[0].rchild = &n[2];
	n[1].lchild = &n[3];
	n[1].rchild = &n[4];
	n[2].lchild = &n[5];
	n[2].rchild = &n[6];
	n[3].lchild = &sen;
	n[3].rchild = &sen;
	n[4].lchild = &sen;
	n[4].rchild = &sen;
	n[5].lchild = &sen;
	n[5].rchild = &sen;
	n[6].lchild = &sen;
	n[6].rchild = &sen;

	judgesym(&n[0], &sen) ? printf("\n对称\n") : printf("\n不对称\n");
	dsprbttree(&n[0], &sen);

	n[5].key = 4;
	judgesym(&n[0], &sen) ? printf("\n对称\n") : printf("\n不对称\n");
	dsprbttree(&n[0], &sen);
#endif 

#else //rbtree

	TstIteratorTraits<int*>::value_type n = 1000;
	printf("%d ", n);

	TstIteratorTraits<TstListIterator<tst_rbtnode>>::value_type i;
	i.key = 99;
	printf("%d ", i);


	TstIteratorTraits<TstListIterator<tst_rbtnode>::value_type*>::value_type j;
	j.key = 110;
	printf("%d ", j.key);


	TstIteratorTraits<tst_rbtnode**>::value_type k = new tst_rbtnode;
	k->key = 1111;
	printf("%d ", k->key);


	TstDestroy(&k);
	//	TstList<int*>::iterator it;
	//	TstList<tst_rbtnode*>::iterator it;
	TstList<tst_rbtnode>::iterator it;

	TstValueType(it);

	TstDestroy(&n);

	TstDestroy(it, it);
#endif
}


void tst_ghc_main()
{
	TstGraphicMtx tgm;

	tgm.create();
	tgm.DispGraphic();
	tgm.TraverseDepthFirst();
	tgm.TraverseBreadthFirst();

}
