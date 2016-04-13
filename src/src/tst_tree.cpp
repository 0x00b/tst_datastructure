#include <stdio.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <stack>
#include "tst_tree.hpp"
#include "tst_queue.hpp"
#include "tst_stack.hpp"


int treehigh(tst_rbtnode* root, tst_rbtnode* sen)
{
	if (root == sen)
	{
		return 0;
	}
	int n1 = 0;
	int n2 = 0;
	n1 = treehigh(root->lchild, sen);
	n2 = treehigh(root->rchild, sen);
	return  (n1 > n2 ? n1 : n2) + 1;
}

int treenodecount(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	if (root == sentinel)
	{
		return 0;
	}
	return 1 + treenodecount( root->lchild, sentinel)+ treenodecount(root->rchild, sentinel);
}

void predsptree(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	if (sentinel == root)
	{
		return;
	}
	printf("%d ", root->key);
	predsptree(root->lchild, sentinel);
	predsptree(root->rchild, sentinel);
}

//遍历-栈
void predsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	TstStack<tst_rbtnode*> s;
	tst_rbtnode* p = root;

	while (p != sentinel || !s.empty())
	{
		while (p != sentinel)
		{
			printf("%d ", p->key);
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->rchild;
		}
	}
}

void predsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	TstStack<tst_rbtnode*> s;
	tst_rbtnode* p = root;

	s.push(p);

	while (!s.empty())
	{
		p = s.top();
		s.pop();
		printf("%d ",p->key);
		if (p->rchild != sentinel)
		{
			s.push(p->rchild);
		}
		if (p->lchild != sentinel)
		{
			s.push(p->lchild);
		}
	}

}

void middsptree(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	if (sentinel == root)
		//if (NULL == root)
	{
		return;
	}
	middsptree(root->lchild, sentinel);
	printf("%d ", root->key);
	middsptree(root->rchild, sentinel);
}

void middsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	TstStack<tst_rbtnode*> s;
	tst_rbtnode* p = root;

	while (p != sentinel || !s.empty())
	{
		while (p != sentinel)
		{
			s.push(p);
			p = p->lchild;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			printf("%d ", p->key);
			p = p->rchild;
		}
	}
}
void middsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel)
{
}

void middsptree_s_s(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	TstStack<tst_rbtnode*> s;
	tst_rbtnode* p = root;
	while (p != sentinel || !s.empty())
	{
		while (p != sentinel)
		{
			s.push(p);
			p = p->rchild;
		}
		if (!s.empty())
		{
			p = s.top();
			s.pop();
			printf("%d ", p->key);
			p = p->lchild;
		}
	}
}


void aftdsptree(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	if (sentinel == root)
	{
		return;
	}
	aftdsptree(root->lchild, sentinel);
	aftdsptree(root->rchild, sentinel);
	printf("%d ", root->key);
}
/*************************************************************
*                         4
*					     /  \
*					    2    6
*				       / \   / \
*				      1   3 5   8
*				     /	        / \
*				    0          7   9
*
*************************************************************/
void aftdsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	tst_rbtnode* p = root;
	tst_rbtnode* visited = sentinel;
	TstStack<tst_rbtnode*> s;

	while (p!=sentinel || !s.empty())
	{
		while (p != sentinel)
		{
			s.push(p);
			p = p->lchild;
		}
		p = s.top();
		if (p->rchild == sentinel || p->rchild == visited)
		{
			printf("%d ",p->key);
			s.pop();
			visited = p;
			p = sentinel;
		}
		else
		{
			p = p->rchild;
		}
	}

}
void aftdsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel)
{
}

static bool _judgesym(tst_rbtnode* l, tst_rbtnode* r, tst_rbtnode* sentinel)
{
	bool b = false;
	if (r != sentinel && l != sentinel)
	{
		if (r->key == l->key)
		{
			b = _judgesym(l->lchild, r->rchild, sentinel);
			if (!b)
			{
				return b;
			}
			return _judgesym(l->rchild, r->lchild, sentinel);
		}
	}
	else if (r == sentinel && l == sentinel)
	{
		return true;
	}
	return false;
}

bool judgesym(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	return _judgesym(root->lchild, root->rchild, sentinel);
}
//镜像
void mirror(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	tst_rbtnode* p;

	if (root == sentinel)
	{
		return;
	}

	p = root->rchild;
	root->rchild = root->lchild;
	root->lchild = p;

	if (root->lchild != sentinel)
	{
		mirror(root->lchild,sentinel);
	}
	if (root->rchild != sentinel)
	{
		mirror(root->rchild, sentinel);
	}
}
/*
* 转换成无头双向循环链表，中序遍历的方式
*/
tst_rbtnode* changetolink(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	TstStack<tst_rbtnode*> s;
	tst_rbtnode* p = root;
	tst_rbtnode* t = sentinel;
	tst_rbtnode* ph = sentinel;
	while (p!=sentinel || !s.empty())
	{
		while (p != sentinel)
		{
			s.push(p);
			p = p->lchild;
		}
		p = s.top();
		s.pop();

		if (ph == sentinel)
		{
			ph = p;
			t = ph;
		}
		else
		{
			t->lchild = p;
			p->parent = t;
			t = t->lchild;
		}
		p = p->rchild;
	}
	ph->parent = sentinel;
	sentinel->lchild = ph;

	t->lchild = sentinel;
	sentinel->parent = t;

	return sentinel;
}

void dsptree(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	TstQueue<tst_rbtnode*> q1;
	TstQueue<tst_rbtnode*> q2;
	tst_rbtnode* p;
	q1.push(root);

	int c = 1;
	int n = treehigh(root, sentinel);
	int m = (int)pow(2, n - 1);

	for (int i = 0; i < m; i++)
	{
		printf("  ");
	}

	printf("%2d%s\n", root->key, root->color ? "红" : "黑");

	while (c)
	{
		c = 0;
		n--;
		for (int i = 0; i < m / 2; i++)
		{
			printf("  ");
		}
		while (!q1.empty())
		{
			p = q1.front();
			sentinel == p ? q2.push(sentinel) : q2.push(p->lchild);
			sentinel == p ? q2.push(sentinel) : q2.push(p->rchild);
			q1.pop();
		}
		while (true)
		{
			p = q2.front();
			if (p != sentinel)
			{
				c++;
				printf("%2d%s", p->key, p->color ? "红" : "黑");
			}
			else
			{
				printf("    ");
			}

			q1.push(p);
			q2.pop();

			if (!q2.empty())
			{
				for (int i = 0; i < m - 2; i++)
				{
					printf("  ");
				}
			}
			else
			{
				m /= 2;
				break;
			}
		}
		printf("\n");
	}

}


void destoytree(tst_rbtnode* root, tst_rbtnode* sentinel)
{
	if (sentinel == root)
	{
		return;
	}

	destoytree(root->lchild, sentinel);
	destoytree(root->rchild, sentinel);

	memset(root, 0x00, sizeof(tst_rbtnode));
	free(root);
	root = NULL;
}