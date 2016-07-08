#include "tst_avltree.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>

extern
void dspavltree(tst_rbtnode* root, tst_rbtnode* sentinel);

tst_rbt_inline int tst_avl_max(int a, int b)
{
	return a < b ? b : a;
}
tst_rbt_inline int tst_avl_height(tst_avlnode* node)
{
	return (NULL == node) ? 0 : node->height;
}

tst_rbt_inline int tst_avl_factor(tst_avlnode* node)
{
	return abs(tst_avl_height(node->rchild) - tst_avl_height(node->lchild));
	 
}

/*************************************************************************************
**    ����ͼ��insert 23 
**
**           30                   30               30                         22   
**           / \                  / \   	       / \        		         /   \  
**          20  31              20  31 		     22   31 			       20     30 
**         / \      ------->    / \    ---->    /   \       ------>	      /      /  \ 
**       18  22               18  22    	  20    23  			    18     23    31
**                                  \         /       				           
**                                  23 	    18        				         
**  �ݹ�
***************************************************************************************/
tst_avlnode* tst_avl_insert(tst_avlnode** root, tst_avlnode* node)
{
	tst_avlnode** p;

	assert(root && node);

	if (NULL == *root)
	{
		*root = node;
		return *root;
	}

	tst_avlnode* q = *root;
	int factor = 0;
	/* insert  & rebalace*/
	if (node->key > q->key)
	{	/* ���������в��� */
		q->rchild = tst_avl_insert(&q->rchild, node);
		tst_avl_set_pa(q->rchild, q);

		factor = tst_avl_factor(q);
		if (2 == factor)
		{	/* ���ƽ�ⱻ������ */
			if (node->key < q->rchild->key)
			{	/* ����ǲ������������������� */
				tst_avl_rotate_right(&q->rchild);
			}
			tst_avl_rotate_left(&q);
		}
	}
	else
	{	/* node->key < q->key ������������ */
		q->lchild = tst_avl_insert(&q->lchild, node);
		tst_avl_set_pa(q->lchild, q);

		factor = tst_avl_factor(q);
		if (2 == factor)
		{	/* ���ƽ�ⱻ������ */
			if (node->key > q->lchild->key)
			{	/* ����ǲ������������������� */
				tst_avl_rotate_left(&q->lchild);
			}
			tst_avl_rotate_right(&q);
		}
	}
	q->height = tst_avl_max(tst_avl_height(q->lchild), tst_avl_height(q->rchild)) + 1;
	return q;
}

/***********************************************
 * �ǵݹ�, ��������˸��ڵ�Ļ����Ǿͺð���
 * ���û�и��ڵ�Ļ����ݹ��ȽϷ���
 * ����汾��������֧û�й��ɡ�����
 **********************************************/
void tst_avl_delete_beta(tst_avlnode** root, tst_avlnode* node)
{
	tst_avlnode* p = NULL;
	tst_avlnode* pNd = NULL;
	int factor = 0;

	assert(root && *root && node);

	if (*root == node)
	{
		/* ���Ҫɾ�����Ǹ��ڵ� */
		//if (NULL == node->lchild&&NULL == node->rchild)
		if (1 == node->height)
		{
			*root = NULL;
			return;
		}
		if (tst_avl_height(node->lchild) < tst_avl_height(node->rchild) )
		{
			pNd = tst_avl_min_node(node->rchild);
		}
		else
		{
			pNd = tst_avl_max_node(node->lchild);
		}
		if (NULL != pNd)
		{
			if (tst_rbt_is_lchild(pNd))
			{
				pNd->parent->lchild = NULL;
			}
			else
			{
				pNd->parent->rchild = NULL;
			}
			p = pNd->parent;
			pNd->lchild = node->lchild;
			tst_avl_set_pa(node->lchild, pNd);
			pNd->rchild = node->rchild;
			tst_avl_set_pa(node->rchild, pNd);
			pNd->height = tst_avl_max(tst_avl_height(pNd->lchild), tst_avl_height(pNd->rchild)) + 1;
			pNd->parent = NULL;
		}
		*root = pNd;
	}
	else
	{
		/* ���node->parent��NULL���� */
		p = node->parent;
		if (NULL == node->lchild)
		{
			/* �����ǿյģ��Һ������� */
			if (tst_rbt_is_lchild(node))
			{
				p->lchild = node->rchild;
				tst_avl_set_pa(node->rchild, p);
			}
			else
			{
				p->rchild = node->rchild;
				tst_avl_set_pa(node->rchild, p);
			}
		}
		else if (NULL == node->rchild)
		{
			/* ���Ӳ��ǿյģ��Һ����ǿյģ��������� */
			if (tst_rbt_is_lchild(node))
			{
				p->lchild = node->lchild;
				tst_avl_set_pa(node->lchild, p);
			}
			else
			{
				p->rchild = node->lchild;
				tst_avl_set_pa(node->lchild, p);
			}
		}
		else
		{
			/* ���Һ��Ӷ����ǿյ� ��ѡ��Ƚϸߵ�һ�ߣ���һ�����ʵĽڵ��滻Ҫɾ���Ľڵ�,�����û����Ͳ��õ����˰�
			*  ����Ƕ����������������������ң������϶�Ҫ����
			*/
			if (tst_avl_height(node->lchild) > tst_avl_height(node->rchild))
			{
				pNd = tst_avl_max_node(node->lchild);

				if (tst_rbt_is_lchild(node))
				{
					if (node == pNd->parent)
					{	/* ���pNd������node�ĺ��� */
						p->lchild = pNd;
						tst_avl_set_pa(pNd, p);
						pNd->rchild = node->rchild;
						tst_avl_set_pa(node->rchild, pNd);
					}
					else
					{
						p->lchild = pNd;
						p = pNd->parent;
						tst_avl_set_pa(pNd, node->parent);
						pNd->lchild = node->lchild;
						tst_avl_set_pa(node->lchild, pNd);
						pNd->rchild = node->rchild;
						tst_avl_set_pa(node->rchild, pNd);
						pNd->height = node->height;
						if (p->lchild == pNd)
						{
							p->lchild = NULL;
						}
						else
						{
							p->rchild = NULL;
						}

					}
				}
				else
				{
					if (node == pNd->parent)
					{	/* ���pNd������node�ĺ��� */
						p->rchild = pNd;
						tst_avl_set_pa(pNd, p);
						pNd->rchild = node->rchild;
						tst_avl_set_pa(node->rchild, pNd);
					}
					else
					{
						p->rchild = pNd;
						p = pNd->parent;
						tst_avl_set_pa(pNd, node->parent);
						pNd->lchild = node->lchild;
						tst_avl_set_pa(node->lchild, pNd);
						pNd->rchild = node->rchild;
						tst_avl_set_pa(node->rchild, pNd);
						pNd->height = node->height;
						if (p->lchild == pNd)
						{
							p->lchild = NULL;
						}
						else
						{
							p->rchild = NULL;
						}
					}
				}
			}
			else
			{
				pNd = tst_avl_min_node(node->rchild);

				if (tst_rbt_is_lchild(node))
				{
					if (node == pNd->parent)
					{	/* ���pNd������node�ĺ��� */
						p->lchild = pNd;
						tst_avl_set_pa(pNd, p);
						pNd->lchild = node->lchild;
						tst_avl_set_pa(node->lchild, pNd);
					}
					else
					{
						p->lchild = pNd;
						p = pNd->parent;
						tst_avl_set_pa(pNd, node->parent);
						pNd->lchild = node->lchild;
						tst_avl_set_pa(node->lchild, pNd);
						pNd->rchild = node->rchild;
						tst_avl_set_pa(node->rchild, pNd);
						pNd->height = node->height;
						if (p->lchild == pNd)
						{
							p->lchild = NULL;
						}
						else
						{
							p->rchild = NULL;
						}
					}
				}
				else
				{
					if (node == pNd->parent)
					{	/* ���pNd������node�ĺ��� */
						p->rchild = pNd;
						tst_avl_set_pa(pNd, p);
						pNd->lchild = node->lchild;
						tst_avl_set_pa(node->lchild, pNd);
					}
					else
					{
						p->rchild = pNd;
						p = pNd->parent;
						tst_avl_set_pa(pNd, node->parent);
						pNd->lchild = node->lchild;
						tst_avl_set_pa(node->lchild, pNd);
						pNd->rchild = node->rchild;
						tst_avl_set_pa(node->rchild, pNd);
						pNd->height = node->height;
						if (p->lchild == pNd)
						{
							p->lchild = NULL;
						}
						else
						{
							p->rchild = NULL;
						}
					}
				}
			}
		}

		p->height = tst_avl_max(tst_avl_height(p->lchild), tst_avl_height(p->rchild)) + 1;
	}

	//dspavltree(*root,NULL);
	/* rebalance */
	while (p && (2 == tst_avl_factor(p)))
	{
		pNd = p->parent; 
		if (NULL != pNd)
		{

			if (tst_rbt_is_lchild(p))
			{
				if (tst_avl_height(p->lchild) < tst_avl_height(p->rchild))
				{
					tst_avl_rotate_left(&p);
				}
				else
				{
					tst_avl_rotate_right(&p);
				}
				pNd->lchild = p;
			}
			else
			{
				if (tst_avl_height(p->lchild) < tst_avl_height(p->rchild))
				{
					tst_avl_rotate_left(&p);
				}
				else
				{
					tst_avl_rotate_right(&p);
				}
				pNd->rchild = p;
			}

		}
		else
		{
			if (tst_avl_height(p->lchild) < tst_avl_height(p->rchild))
			{
				tst_avl_rotate_left(&p);
			}
			else
			{
				tst_avl_rotate_right(&p);
			}
			*root = p;
		}
		p = p->parent;
	}

}


/***********************************************
* delete
**********************************************/
void tst_avl_delete(tst_avlnode** root, tst_avlnode* node)
{
	tst_avlnode* p = NULL;
	tst_avlnode* pNd = NULL;
	int factor = 0;

	assert(root && *root && node);

	/* ���ҵ��滻�Ľڵ� */
	if (NULL == node->lchild)
	{
		pNd = node->rchild;
	}
	else if (NULL == node->rchild)
	{
		pNd = node->lchild;
	}
	else
	{
		if (tst_avl_height(node->lchild) < tst_avl_height(node->rchild))
		{
			pNd = tst_avl_min_node(node->rchild);
		}
		else
		{
			pNd = tst_avl_max_node(node->lchild);
		}
	}

	/* �滻 node��node�Ƴ����� */
	p = node->parent;
	tst_avl_set_pa(pNd, p);
	if (NULL != p)
	{
		if (tst_rbt_is_lchild(node))
		{
			p->lchild = pNd;
		}
		else
		{
			p->rchild = pNd;
		}
	}
	else
	{
		*root = pNd;
	}
	if (node->lchild == pNd)
	{
		pNd->rchild = node->rchild;
		tst_avl_set_pa(pNd->rchild, pNd);
	}
	else if (node->rchild == pNd)
	{
		pNd->lchild = node->lchild;
		tst_avl_set_pa(pNd->lchild, pNd);
	}
	else
	{
		pNd->lchild = node->lchild;
		tst_avl_set_pa(pNd->lchild, pNd);
		pNd->rchild = node->rchild;
		tst_avl_set_pa(pNd->rchild, pNd);
	}

	/* */
	return;
}


/*************************************************************************************
**    ����ͼ��insert 23
**
**           30                   30               30                         22
**           / \                  / \      R       / \        		         /   \
**          20  31              20  31 	<----    22   31 			       20     30
**         / \      ------->    / \    ---->    /   \       ------>	      /      /  \
**       18  22               18  22      L   20    23  			    18     23    31
**                               /  \         / \ 
**                                  23 	    18   
**
***************************************************************************************/
tst_avlnode* tst_avl_rotate_left(tst_avlnode** node)
{
	tst_avlnode* p;

	p = (*node)->rchild;
	tst_avl_set_pa(p, (*node)->parent);
	(*node)->rchild = p->lchild;
	tst_avl_set_pa(p->lchild, *node);//p->lchild->parent = *node;
	p->lchild = *node;
	tst_avl_set_pa(*node, p);
	*node = p;

	p->lchild->height = tst_avl_max(tst_avl_height(p->lchild->lchild), tst_avl_height(p->lchild->rchild)) + 1;
	p->height = tst_avl_max(tst_avl_height(p->lchild), tst_avl_height(p->rchild)) + 1;
	return p;
}
tst_avlnode* tst_avl_rotate_right(tst_avlnode** node)
{
	tst_avlnode* p;

	p = (*node)->lchild;
	tst_avl_set_pa(p, (*node)->parent);
	(*node)->lchild = p->rchild;
	tst_avl_set_pa(p->rchild, *node);
	p->rchild = *node;
	tst_avl_set_pa(*node, p);
	*node = p;

	p->rchild->height = tst_avl_max(tst_avl_height(p->rchild->lchild), tst_avl_height(p->rchild->rchild)) + 1;
	p->height = tst_avl_max(tst_avl_height(p->lchild), tst_avl_height(p->rchild)) + 1;
	return p;
}

tst_avlnode* tst_avl_max_node(tst_avlnode* node)
{
	while (node->rchild != NULL)
	{
		node = node->rchild;
	}
	return node;
}