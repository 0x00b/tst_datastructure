#include "tst_avltree.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

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
**    如下图：insert 23
**
**           30                   30               30                         22
**           / \                  / \   	       / \        		         /   \
**          20  31              20  31 		     22   31 			       20     30
**         / \      ------->    / \    ---->    /   \       ------>	      /      /  \
**       18  22               18  22    	  20    23  			    18     23    31
**                                  \         /
**                                  23 	    18
**  递归
***************************************************************************************/
tst_avlnode* tst_avl_insert(tst_avlnode** root, tst_avlnode* node)
{
	assert(root && node);

	if (NULL == *root)
	{
		*root = node;
		return *root;
	}

	tst_avlnode** q = root;
	int factor = 0;
	/* insert  & rebalace*/
	if (node->key > (*q)->key)
	{	/* 往右子树中插入 */
		(*q)->rchild = tst_avl_insert(&(*q)->rchild, node);
		tst_avl_set_pa((*q)->rchild, (*q));

		factor = tst_avl_factor((*q));
		if (2 == factor)
		{	/* 如果平衡被打破了 */
			if (node->key < (*q)->rchild->key)
			{	/* 如果是插入在右子树的左子树 */
				tst_avl_rotate_right(&(*q)->rchild);
			}
			tst_avl_rotate_left(q);
		}
	}
	else
	{	/* node->key < (*q)->key 插入在左子树 */
		(*q)->lchild = tst_avl_insert(&(*q)->lchild, node);
		tst_avl_set_pa((*q)->lchild, (*q));

		factor = tst_avl_factor(*q);
		if (2 == factor)
		{	/* 如果平衡被打破了 */
			if (node->key > (*q)->lchild->key)
			{	/* 如果是插入在右子树的左子树 */
				tst_avl_rotate_left(&(*q)->lchild);
			}
			tst_avl_rotate_right(q);
		}
	}
	(*q)->height = tst_avl_max(tst_avl_height((*q)->lchild), tst_avl_height((*q)->rchild)) + 1;
	return (*q);
}

/***********************************************
* 非递归, 如果保存了父节点的话。那就好办了
* 如果没有父节点的话，递归会比较方便
* 最初版本。。。分支没有归纳。。。
**********************************************/
void tst_avl_delete_beta(tst_avlnode** root, tst_avlnode* node)
{
	tst_avlnode* p = NULL;
	tst_avlnode* pNd = NULL;
	int factor = 0;

	assert(root && *root && node);

	if (*root == node)
	{
		/* 如果要删除的是根节点 */
		//if (NULL == node->lchild&&NULL == node->rchild)
		if (1 == node->height)
		{
			*root = NULL;
			return;
		}
		if (tst_avl_height(node->lchild) < tst_avl_height(node->rchild))
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
		/* 如果node->parent是NULL？？ */
		p = node->parent;
		if (NULL == node->lchild)
		{
			/* 左孩子是空的，右孩子上移 */
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
			/* 左孩子不是空的，右孩子是空的，左孩子上移 */
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
			/* 左右孩子都不是空的 ，选择比较高的一边，找一个合适的节点替换要删除的节点,运气好或许就不用调整了吧
			*  如果是都从左子树或者右子树中找，基本上都要调整
			*/
			if (tst_avl_height(node->lchild) > tst_avl_height(node->rchild))
			{
				pNd = tst_avl_max_node(node->lchild);

				if (tst_rbt_is_lchild(node))
				{
					if (node == pNd->parent)
					{	/* 如果pNd正好是node的孩子 */
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
					{	/* 如果pNd正好是node的孩子 */
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
					{	/* 如果pNd正好是node的孩子 */
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
					{	/* 如果pNd正好是node的孩子 */
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
	/* rebalance ,还有bug，不想写了*/
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
	tst_avlnode* q = NULL;
	tst_avlnode* pNd = NULL;
	int factor = 0;

	assert(root && *root && node);

	/* 先找到替换的节点 */
	if (NULL == node->lchild)
	{	/* 查找情况1 */
		pNd = node->rchild;
		p = node;
	}
	else if (NULL == node->rchild)
	{	/* 查找情况2 */
		pNd = node->lchild;
		p = node;
	}
	else
	{	/* 查找情况3 ,从比较高的一边去找一个节点来替换要删除的点，这样不需要调整的可能性比较大*/
		if (tst_avl_height(node->lchild) < tst_avl_height(node->rchild))
		{
			p = tst_avl_min_node(node->rchild);
		}
		else
		{
			p = tst_avl_max_node(node->lchild);
		}
		if (NULL == p->lchild)
		{
			pNd = p->rchild;
		}
		else
		{
			pNd = p->lchild;
		}
	}
	if (p == *root)
	{	/* 只会是查找情况1,2，因为情况3已经是从左右孩子中去找p，p不可能是*root */
		*root = pNd;
		pNd->parent = NULL;
		tst_rbt_node_reset(node);
		return;
	}

	/* 经过p == *root判断后， node/p->parent 不会是NULL了。
	* 替换 node，node移出树外 */

	/* 找到的节点（p）拿到树外 */

	q = tst_rbt_parent(p);

	if (tst_rbt_is_lchild(p))
	{
		tst_rbt_parent(p)->lchild = pNd;
	}
	else
	{
		tst_rbt_parent(p)->rchild = pNd;
	}

	if (p == node)
	{
		tst_avl_set_pa(pNd, tst_rbt_parent(p));
	}
	else
	{
		if (tst_rbt_parent(p) == node)
		{
			tst_avl_set_pa(pNd, tst_rbt_grandpa(p));
			q = tst_rbt_grandpa(p);
		}
		else
		{
			tst_avl_set_pa(pNd, tst_rbt_parent(p));
		}
		/* p拿到树外之后，替换需要删除的node */
		tst_avl_set_pa(p, tst_rbt_parent(node));
		p->lchild = node->lchild;
		tst_avl_set_pa(p->lchild, p);
		p->rchild = node->rchild;
		tst_avl_set_pa(p->rchild, p);
		//p->height = node->height;
		p->height = tst_avl_max(tst_avl_height(p->lchild), tst_avl_height(p->rchild)) + 1;

		if (node == *root)
		{	/* 如果要删除的是根节点，p替换根节点，否则如下 */
			*root = p;
		}
		else
		{
			if (tst_rbt_is_lchild(node))
			{
				tst_rbt_parent(node)->lchild = p;
			}
			else
			{
				tst_rbt_parent(node)->rchild = p;
			}
		}

	}

	//q->height = tst_avl_max(tst_avl_height(q->lchild), tst_avl_height(q->rchild)) + 1;

	//dspavltree(*root, NULL);
	/* rebalance */

	while (q)
	{
		q->height = tst_avl_max(tst_avl_height(q->lchild), tst_avl_height(q->rchild)) + 1;
		pNd = q;
		if (2 == tst_avl_factor(q))
		{
			if (tst_avl_height(q->lchild) < tst_avl_height(q->rchild))
			{
				if (pNd == *root)
				{
					*root = tst_avl_rotate_left(&q);
				}
				else
				{
					tst_rbt_is_lchild(q)
						? (tst_rbt_parent(q)->lchild = tst_avl_rotate_left(&q))
						: (tst_rbt_parent(q)->rchild = tst_avl_rotate_left(&q));
				}
			}
			else
			{
				if (pNd == *root)
				{
					*root = tst_avl_rotate_right(&q);
				}
				else
				{
					tst_rbt_is_lchild(q)
						? (tst_rbt_parent(q)->lchild = tst_avl_rotate_right(&q))
						: (tst_rbt_parent(q)->rchild = tst_avl_rotate_right(&q));
				}
			}
		}
		q = tst_rbt_parent(q);
	}
	return;
}


/*************************************************************************************
**    如下图：insert 23
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