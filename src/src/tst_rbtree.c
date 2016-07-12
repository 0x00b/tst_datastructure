/*
** tst_rbtree.c
** create by lj
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "tst_rbtree.h"


void dsptree(tst_rbtnode* root, tst_rbtnode* sentinel);

static tst_rbt_inline void tst_rbt_rotate_left(tst_rbtnode** root, tst_rbtnode* node, tst_rbtnode* sentinel);
static tst_rbt_inline void tst_rbt_rotate_right(tst_rbtnode** root, tst_rbtnode* node, tst_rbtnode* sentinel);

/*
* ����������Ĳ���
*/
void tst_rbt_insert_default(tst_rbtnode* parent, tst_rbtnode* node, tst_rbtnode* sentinel)
{
	tst_rbtnode** p;

	/*
	Ϊɶ�е���ϲ��for����ѭ���أ���Ϊ�����Ż�֮����һ��jmp����while��true������Ҫtest����cmp�Ƚϡ���ָ��
	*/
	for (;;)
	{
		p = (node->key < parent->key) ? &parent->lchild : &parent->rchild;
		if (*p == sentinel)	/*  �ҵ���Ҷ�ӽڵ�����   */
		{
			break;
		}
		parent = *p;
	}

	*p = node;
	node->parent = parent;
	node->lchild = sentinel;
	node->rchild = sentinel;
	/* ��ǰ���Ϊ��ɫ�������õĻ������ڵ���ɫ�Ǻ�ɫ�������õ����� */
	tst_rbt_set_red(node);
}

void tst_rbt_insert(tst_rbtree* tree, tst_rbtnode* node)
{
	assert(tree && node);

	tst_rbtnode *sen, **root;
	root = &tree->root;
	sen = tree->sentinel;

	/* �²���ĵ��Ǹ��ڵ� */
	if (*root == sen)
	{
		*root = node;
		node->parent = NULL;
		node->lchild = sen;
		node->rchild = sen;
		tst_rbt_set_black(node);

		return;
	}

	/* ���������tst_rbt_insert_default���� */
	tree->insert(*root, node, sen);

	/* ����ƽ������ */
	while (node != *root && tst_rbt_is_red(tst_rbt_parent(node)))
	{
		/* node���ڵ��Ǻ�ɫ  */
		if (tst_rbt_parent(node) == tst_rbt_grandpa(node)->lchild)
		{	
			/* ���ڵ����游������ */
			if (tst_rbt_is_red(tst_rbt_lruncle(node, r)))
			{
				/* �����Ǻ�ɫ��������ɫ */
				tst_rbt_set_red(tst_rbt_grandpa(node));
				tst_rbt_set_black(tst_rbt_parent(node));
				tst_rbt_set_black(tst_rbt_lruncle(node, r));
				node = tst_rbt_grandpa(node);
				/* ѭ����ȥ�ٿ�node��parent����� */
				/* ������󵽸��ڵ㣬���ʱ����ڵ����óɺ�ɫ����Ҫ�������ø��ڵ�Ϊ��ɫ */
			}
			else
			{
				/* �����Ǻ�ɫ����ת�� */
				if (tst_rbt_is_rchild(node))
				{
					/* ���ڵ������ӣ��Լ����Һ��ӣ����ʱ������Լ������ף��游���������ɱպ�ͼ�������� */
					node = tst_rbt_parent(node);
					tst_rbt_rotate_left(root, node, sen);
				}
				tst_rbt_set_red(tst_rbt_grandpa(node));
				tst_rbt_set_black(tst_rbt_parent(node));
				tst_rbt_rotate_right(root, tst_rbt_grandpa(node), sen);
				/* ��ת֮���ok��ѭ������ */
			}
		}
		else
		{	
			/* ���ڵ����游���Һ��ӣ������������ӵĲ����෴�ͺá� */
			if (tst_rbt_is_red(tst_rbt_lruncle(node,l)))
			{	
				/* �����Ǻ�ɫ��������ɫ */
				tst_rbt_set_red(tst_rbt_grandpa(node));
				tst_rbt_set_black(tst_rbt_parent(node));
				tst_rbt_set_black(tst_rbt_lruncle(node,l));
				node = tst_rbt_grandpa(node);
			}
			else
			{
				if (tst_rbt_is_lchild(node))
				{
					node = tst_rbt_parent(node);
					tst_rbt_rotate_right(root, node, sen);
				}
				tst_rbt_set_red(tst_rbt_grandpa(node));
				tst_rbt_set_black(tst_rbt_parent(node));
				tst_rbt_rotate_left(root, tst_rbt_grandpa(node), sen);
			}

		}
	}
	tst_rbt_set_black(*root);
	return;
}


void tst_rbt_delete(tst_rbtree* tree, tst_rbtnode* node)
{
	tst_rbtnode **root, *subt, *temp, *sentinel, *w;
	root = &tree->root;
	sentinel = tree->sentinel;
	
	/* ��������ɾ�� */
	
	/* �ҵ�Ҫɾ���Ľڵ㡣 */
	if (sentinel == node->lchild)		//fd1
	{
		subt = node->rchild;
		temp = node;
	}
	else if (sentinel == node->rchild)	//fd2
	{
		subt = node->lchild;
		temp = node;
	}
	else								//fd3
	{
		/* node�����Һ��Ӷ���Ϊ�գ���ô�����������ҵ�key��С�Ľڵ㣬����node������㣬��ɾ��node  */
		temp = tst_rbt_min_node(node->rchild, sentinel);
		if (temp->lchild == sentinel)
		{	
			/* ��Ȼ����С�Ľڵ㣬һ�����������֧������������ӣ�temp�϶�������С�� */
			subt = temp->rchild;
		}
		else
		{
			subt = temp->lchild;
		}
	}
	/* ���Ҫɾ���ĵ��Ǹ��ڵ㣬�������ֻ����fd1��fd2�е�һ�� */
	if (temp == *root)
	{
		*root = subt;
		tst_rbt_set_black(subt);
		tst_rbt_node_reset(node);
		return;
	}

	unsigned char isRed = tst_rbt_is_red(temp);

	/* ���ҵ��Ľڵ��Ƴ����⡣��������  */
	if (tst_rbt_is_lchild(temp))
	{
		tst_rbt_parent(temp)->lchild = subt;
	}
	else
	{
		tst_rbt_parent(temp)->rchild = subt;
	}
	if (temp == node)
	{	
		/* ���Ҫɾ���ĵ����node����ônode�Ѿ����Ƴ����� */
		subt->parent = temp->parent;
	}
	else
	{
		/* ���Ҫɾ���ĵ㲻��node����������������С�Ľڵ� */

		if (node == tst_rbt_parent(temp))
		{
			/* ���node��temp�ĸ��ڵ㣬��ô��subt�ĸ��ڵ㻹��temp���������subt��sentinel����ôsentinelһ��ʼparent��NULL */
			subt->parent = temp;
		}
		else
		{
			/* ������ǣ���ôsubt�ĸ��ڵ����temp�ĸ��ڵ� */
			subt->parent = temp->parent;
		}

		temp->parent = node->parent;
		temp->lchild = node->lchild;
		temp->rchild = node->rchild;
		tst_rbt_copy_color(temp, node);

		if (node == *root)
		{
			/* ���node�Ǹ������ø�Ϊ�ҵ��Ľڵ� */
			*root = temp;
		}
		else
		{
			/* ���ҵ��ĵ��滻node  */
			if (tst_rbt_is_lchild(node))
			{
				tst_rbt_parent(node)->lchild = temp;
			}
			else
			{
				tst_rbt_parent(node)->rchild = temp;
			}
		}

		if (!tst_rbt_is_leaf(tree, temp->lchild))
		{
			temp->lchild->parent = temp;
		}
		if (!tst_rbt_is_leaf(tree, temp->rchild))
		{
			temp->rchild->parent = temp;
		}
	}

	tst_rbt_node_reset(node);
	
	if (isRed)
	{
		return;
	}


	/* ����ƽ������ */
	while (subt != *root && tst_rbt_is_black(subt))
	{
		if (tst_rbt_is_lchild(subt))
		{
			w = tst_rbt_parent(subt)->rchild;
			/* �������1��
			*�ֵ��Ǻ�ɫ����ô���ڵ㣬�ֵܵĺ��Ӷ��Ǻ�ɫ�������ֵ��븸�׵���ɫ
			*Ȼ��������ת�����ΪҪɾ���ĵ���ֵ��Ǻ�ɫ��
			*/
			if (tst_rbt_is_red(w))/*w�Ǻ�ɫ����w��parent��child��Ȼ�Ǻ�ɫ*/
			{
				tst_rbt_set_red(tst_rbt_parent(subt));
				tst_rbt_set_black(w);
				tst_rbt_rotate_left(root, tst_rbt_parent(subt), sentinel);
				w = tst_rbt_parent(subt)->rchild;/*ת��Ϊsubt���ֵ��Ǻ�ɫ�����*/
			}
			/* �������2��
			*���Ҫɾ���ĵ���ֵܲ��Ǻ�ɫ�������ֵܵ����Һ��Ӷ��Ǻ�ɫ
			*��ô���ֵ�Ⱦ�ɺ�ɫ���ٿ����ڵ㡣����Ǻ�ɫ������ѭ�������Ⱦ�ɺ�ɫ��ok
			*������ڵ��Ǻ�ɫ����ô�ֻص���ԭʼ�����⣨���1234�����ܣ�
			*/
			if (tst_rbt_is_black(w->lchild) && tst_rbt_is_black(w->rchild))
			{
				tst_rbt_set_red(w);
				subt = tst_rbt_parent(subt);
			}
			else
			{
				/* �������3���ֵܽڵ��к�ɫ����
				*����ֵܵ�Զֶ���Ǻ�ɫ����ô�϶�����ֶ���Ǻ�ɫ��
				*����Ŀ���ǰ�Զֶ�ӱ�ɺ�ɫ��ת������һ��������������ս�����⡣
				*/

				if (tst_rbt_is_black(w->rchild))
				{
					tst_rbt_set_black(w->lchild);
					tst_rbt_set_red(w);
					tst_rbt_rotate_right(root, w, sentinel);
					w = tst_rbt_parent(subt)->rchild;
				}

				/* �������4��
				*���Զֶ���Ǻ�ɫ��ֱ�Ӱ�Զֶ����Ϊ��ɫ�������������ֵ���ɫ
				*����ѡ����ʵ���ת������ת�������ﵽƽ�⡣
				*/
				tst_rbt_copy_color(w, tst_rbt_parent(subt));
				tst_rbt_set_black(tst_rbt_parent(subt));
				tst_rbt_set_black(w->rchild);
				tst_rbt_rotate_left(root, tst_rbt_parent(subt), sentinel);
				subt = *root;/* ����ѭ����ͬʱ����������ø��ڵ�Ϊ��ɫ */
			}

		}
		else
		{
			/* �����棬ɾ�����Ǹ��׵��������ƣ�ֻ��������ת����ʱ��������������෴ */
			w = tst_rbt_parent(subt)->lchild;
			if (tst_rbt_is_red(w))/* w�Ǻ�ɫ��w��parent��child��Ȼ�Ǻ�ɫ */
			{
				tst_rbt_set_black(w);
				tst_rbt_set_red(tst_rbt_parent(subt));
				tst_rbt_rotate_right(root, tst_rbt_parent(subt), sentinel);
				w = tst_rbt_parent(subt)->lchild;
			}
			if (tst_rbt_is_black(w->lchild) && tst_rbt_is_black(w->rchild))
			{
				tst_rbt_set_red(w);
				subt = tst_rbt_parent(subt);
			}
			else
			{
				if (tst_rbt_is_black(w->lchild))
				{
					tst_rbt_set_red(w);
					tst_rbt_set_black(w->rchild);
					tst_rbt_rotate_left(root, w, sentinel);
					w = tst_rbt_parent(subt)->lchild;
				}
				tst_rbt_copy_color(w, tst_rbt_parent(subt));
				tst_rbt_set_black(tst_rbt_parent(subt));
				tst_rbt_set_black(w->lchild);
				tst_rbt_rotate_right(root, tst_rbt_parent(subt), sentinel);
				subt = *root;
			}

		}
	}
	tst_rbt_set_black(subt);
}


tst_rbtnode* tst_rbt_find(tst_rbtree* tree, tst_rbtnode* sentinel,unsigned int key)
{
	tst_rbtnode* root = tree->root;

	while (sentinel != root)
	{
		if (key == root->key)
		{
			return root;
		}
		root = key < root->key ? root->lchild : root->rchild;
	}
	return NULL;
}

tst_rbt_inline tst_rbtnode* tst_rbt_min_node(tst_rbtnode* node, tst_rbtnode* sentinel)
{
	while (node->lchild != sentinel)
	{
		node = node->lchild;
	}
	return node;
}

/*************************************************************************************
**    ����ͼ��20 ����ڵ����� ���� ����
**                                                                                   
**           30                  30    		          10                   10        
**           / \                 / \		          / \                  / \       
**          20  31    ����      22   31		         9   20      ����     9   22     
**         / \      ------->   / \          ����        / \     ------->     / \      
**       18  22    <-------   20  23                  18   22  <--------   20   23  
**           / \      ����   / \   			               / \   ����     / \     	
**         21   23          18  21			              21  23        18   21   	
**         										     					  			   
***************************************************************************************/
static tst_rbt_inline void 
tst_rbt_rotate_left(tst_rbtnode** root, tst_rbtnode* node, tst_rbtnode* sentinel)
{
	tst_rbtnode* temp;

	temp = node->rchild;
	node->rchild = temp->lchild;	/* �൱�ڰ�21���20���Һ��� */

	if (temp->lchild != sentinel)
	{
		temp->lchild->parent = node;/* 21λ�øı�֮��������������parent */
	}
	if (node == *root)
	{
		*root = temp;				/* ���node�Ǹ��ڵ㡣��temp�Ǹ��ڵ� */ 
	}
	else if (node == tst_rbt_parent(node)->lchild )
	{
		tst_rbt_parent(node)->lchild = temp;/* ��һͼ��node�ڸ��ڵ�����ӽڵ� */ 
	}
	else
	{
		tst_rbt_parent(node)->rchild = temp;/* �ڶ�ͼ��node�ڸ��ڵ���Һ��ӽڵ� */
	}
	temp->parent = tst_rbt_parent(node);
	temp->lchild = node;
	node->parent = temp;

}

static tst_rbt_inline void 
tst_rbt_rotate_right(tst_rbtnode** root, tst_rbtnode* node, tst_rbtnode* sentinel)
{
	tst_rbtnode* temp;
	temp = node->lchild;
	node->lchild = temp->rchild;

	if (temp->rchild != sentinel)
	{
		temp->rchild->parent = node;
	}

	if (node == *root)
	{
		*root = temp;
	}
	else if (node == tst_rbt_parent(node)->lchild)
	{
		tst_rbt_parent(node)->lchild = temp;
	}
	else
	{
		tst_rbt_parent(node)->rchild = temp;
	}
	temp->parent = tst_rbt_parent(node);
	temp->rchild = node;
	node->parent = temp;
}

