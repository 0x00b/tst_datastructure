#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include "tst_tree.hpp"
#include "tst_queue.hpp"
#include "tst_list.hpp"
#include "tst_stack.hpp"

extern "C"{
#include "tst_rbtree.h"
#include "tst_avltree.h"

}
using namespace std;

#define len 12

void tst_avl_main();
void tst_rbt_main();

int main(int argc, char* args[])
{
#if 1
	tst_avl_main();
#else
	tst_rbt_main();
#endif

#if defined(_WIN32) || defined(_WIN64)
	return system("pause");
#else
	return 0;
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
		tst_avl_node_init(node[i], i );
		root = tst_avl_insert(&root, node[i]); dspavltree(root); printf("\n");
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

#elif 1
	printf("delete:3 5 2 6\n");
	tst_avl_delete(&root, node[3]);

	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[5]);
	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[2]);
	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[6]);
	dspavltree(root); printf("\n");
	tst_avl_delete(&root, node[9]);
	dspavltree(root); printf("\n");
#else 

	printf("delete:\n");
	for (int i = len-1; i >0 ; i--)
	{
		//tst_avl_delete_beta(&root, node[i]);
		printf("del[%d]\n",i);
		tst_avl_delete(&root, node[i]);
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
		tst_rbt_node_init(node[i], i+1);
		tst_rbt_insert(&t, node[i]);
		dsprbttree(t.root, t.sentinel); printf("\n"); 
	}
	/* 显示树 */
	
	printf("tree node count:%d  tree height:%d\n",\
		treenodecount(t.root, t.sentinel), treehigh(t.root,t.sentinel));
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
}

