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
#include "tst_stack_app.h"

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

/*
 * 栈的应用，中缀表达式，后缀表达式
 *
 */
void tst_stack_main() 
{
	char str[100]; 
	bool bret = false;

#if 0
	TstList<string> lst_mid_formula; /* 中缀表达式*/
	TstList<string> lst_aft_formula; /* 后缀表达式*/
	cout << "input math formula:" << endl;
	cin>> str;

	/* 拆分出表达式的各元素，按照原来的顺序放在队列中 */
	bret = split_formula(str, lst_mid_formula);
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

		printf( "\n表达式结果：%.10lf\n" ,calculate(lst_aft_formula));
	}
#elif 0
	cout << "括号匹配：" << endl;
	cout << "input some bracket(eg:[()][{()}]):";
	cin >> str;
	bret = match_bracket(str);
	cout << (bret ? "括号匹配" : "括号不匹配") << endl;
#elif 1
	edit_row();

#elif 1
	cout << "迷宫求解：" << endl;
	TstStack<Point> trail;
	Maze maze{/* 2是出入口*/
	{	//0,1,2,3,4,5,6,7,8,9
		{ 0,2,0,0,0,0,0,2,0,0 },//0
		{ 0,1,0,0,1,1,1,1,0,0 },//1
		{ 0,1,1,1,0,0,0,0,1,0 },//2
		{ 0,0,0,1,0,1,1,1,0,0 },//3
		{ 0,1,1,1,1,1,0,1,0,0 },//4
		{ 0,1,0,0,0,1,0,1,0,0 },//5
		{ 0,1,1,1,0,1,0,1,0,0 },//6
		{ 0,0,0,0,0,0,0,1,0,0 },//7
		{ 0,0,0,1,1,1,1,1,1,0 },//8
		{ 0,0,0,0,2,0,0,0,0,0 }	//9
	} };
	bret = maze_out(maze, maze.n, Point(0, 1), trail);
	for (int i = 0; i < maze.n; i++)
	{
		for (int j = 0; j < maze.n; j++)
		{
			cout << maze.mz[i][j]<<" ";
		}
		cout << endl;
	}
	if (bret)
	{
		cout << "路径如下：" << endl;
		while (!trail.empty())
		{
			Point& p = trail.top();
			cout << "<--(" << p.x << "," << p.y << ")";
			trail.pop();
		}
		cout << endl;
	}
	else
	{
		cout << "没有通路！" << endl;
	}


#elif 0
	cout << "进制转换：" << endl;
	TstStack<char> ch_stk;
	int num = 0;
	cout << "input a number:";
	cin >> num;
	num_conversion(num, 2, ch_stk);
	cout << "\n二进制：";
	while (!ch_stk.empty())
	{
		cout << ch_stk.top();
		ch_stk.pop();
	}
	cout << endl;
	num_conversion(num, 8, ch_stk);
	cout << "\n八进制：";
	while (!ch_stk.empty())
	{
		cout << ch_stk.top();
		ch_stk.pop();
	}
	cout << endl;
	num_conversion(num, 16, ch_stk);
	cout << "\n十六进制：0x";
	while (!ch_stk.empty())
	{
		cout << ch_stk.top();
		ch_stk.pop();
	}
	cout << endl;

#endif
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
