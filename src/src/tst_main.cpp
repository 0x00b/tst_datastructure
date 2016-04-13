#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "tst_tree.hpp"
#include "tst_queue.hpp"
#include "tst_list.hpp"
#include "tst_stack.hpp"
#include "tst_rbtree.h"

using namespace std;

#define len 11

int main(int argc, char* args[])
{
//	queue<tst_rbtnode*> q;

#if 1
	tst_rbtree t;
	tst_rbtnode sen;
	tst_rbtnode* node[len];

	tst_rbt_node_init(&sen, 0);

	tst_rbt_init(&t, &sen, tst_rbt_insert_default);

	for (int i = 0; i < len; i++)
	{
		node[i] = (tst_rbtnode*)malloc(sizeof(tst_rbtnode));
		tst_rbt_node_init(node[i], i+1);
		tst_rbt_insert(&t, node[i]);
//		dsptree(t.root, t.sentinel); printf("\n");
	}
	//显示树
	printf("tree node count:%d  tree height:%d\n",\
		treenodecount(t.root, t.sentinel), treehigh(t.root,t.sentinel));
	printf("tree:\n");
	dsptree(t.root, t.sentinel); printf("\n");

#if 1
	printf("前序dg:");
	predsptree(t.root, t.sentinel); 
	printf("\n");
	printf("前序s1:");
	predsptree_s_1(t.root, t.sentinel);
	printf("\n");
	printf("前序s2:");
	predsptree_s_2(t.root, t.sentinel);
	printf("\n\n");

	printf("中序dg:");
	middsptree(t.root, t.sentinel);
	printf("\n");
	printf("中序s1:");
	middsptree_s_1(t.root, t.sentinel);
	printf("\n");
	printf("逆中序:");
	middsptree_s_s(t.root, t.sentinel);
	printf("\n\n");

	printf("后序dg:"); 
	aftdsptree(t.root, t.sentinel); 
	printf("\n");
	printf("后序s1:");
	aftdsptree_s_1(t.root, t.sentinel);
	printf("\n");

#endif
	tst_rbtnode* p;
	//删除节点
#if 1
	p = tst_rbt_find(&t, t.sentinel, 8);
	printf("\n del find = %d:\n", p ? p->key : -1);
/*
	p = tst_rbt_min_node(t.root->rchild, t.sentinel);
	printf("min=%d\n", p ? p->key : -1);
*/
	tst_rbt_delete(&t, p);
	free(p);
	dsptree(t.root, t.sentinel); printf("\n");
	printf("\n");
#endif

#if 1
	printf("mirror:\n");
	mirror(t.root, t.sentinel);
	dsptree(t.root, t.sentinel); printf("\n");
#endif

#if 1
	printf("\n转换成双向循环链表:\n");
	tst_rbtnode* ph = changetolink(t.root,t.sentinel);

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

	//释放
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
	dsptree(&n[0], &sen);

	n[5].key = 4;
	judgesym(&n[0], &sen) ? printf("\n对称\n") : printf("\n不对称\n");
	dsptree(&n[0], &sen);
#endif 

#else //rbtree

	TstIteratorTraits<int*>::value_type n = 1000;
	printf("%d ", n);

	TstIteratorTraits<TstListIterator<tst_rbtnode>>::value_type i;
	i.key = 99;
	printf("%d ", i);


	TstIteratorTraits<TstListIterator<tst_rbtnode>::value_type*>::value_type j;
	j.key = 110;
	printf("%d ",j.key);


	TstIteratorTraits<tst_rbtnode**>::value_type k = new tst_rbtnode;
	k->key = 1111;
	printf("%d ", k->key);


	TstDestroy(&k);
//	TstList<int*>::iterator it;
//	TstList<tst_rbtnode*>::iterator it;
	TstList<tst_rbtnode>::iterator it;

	TstValueType(it);

	TstDestroy(&n);

	TstDestroy(it ,it);
#endif
	return 0;
}

