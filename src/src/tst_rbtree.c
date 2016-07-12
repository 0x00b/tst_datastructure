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
* 二叉查找树的插入
*/
void tst_rbt_insert_default(tst_rbtnode* parent, tst_rbtnode* node, tst_rbtnode* sentinel)
{
	tst_rbtnode** p;

	/*
	为啥有的人喜欢for做死循环呢？因为编译优化之后是一个jmp，而while（true）还需要test或者cmp比较。多指令
	*/
	for (;;)
	{
		p = (node->key < parent->key) ? &parent->lchild : &parent->rchild;
		if (*p == sentinel)	/*  找到了叶子节点上了   */
		{
			break;
		}
		parent = *p;
	}

	*p = node;
	node->parent = parent;
	node->lchild = sentinel;
	node->rchild = sentinel;
	/* 当前结点为红色。运气好的话，父节点颜色是黑色，还不用调整。 */
	tst_rbt_set_red(node);
}

void tst_rbt_insert(tst_rbtree* tree, tst_rbtnode* node)
{
	assert(tree && node);

	tst_rbtnode *sen, **root;
	root = &tree->root;
	sen = tree->sentinel;

	/* 新插入的点是根节点 */
	if (*root == sen)
	{
		*root = node;
		node->parent = NULL;
		node->lchild = sen;
		node->rchild = sen;
		tst_rbt_set_black(node);

		return;
	}

	/* 调用上面的tst_rbt_insert_default（） */
	tree->insert(*root, node, sen);

	/* 重新平衡红黑树 */
	while (node != *root && tst_rbt_is_red(tst_rbt_parent(node)))
	{
		/* node父节点是红色  */
		if (tst_rbt_parent(node) == tst_rbt_grandpa(node)->lchild)
		{	
			/* 父节点是祖父的左孩子 */
			if (tst_rbt_is_red(tst_rbt_lruncle(node, r)))
			{
				//叔叔是红色。调整颜色
				tst_rbt_set_red(tst_rbt_grandpa(node));
				tst_rbt_set_black(tst_rbt_parent(node));
				tst_rbt_set_black(tst_rbt_lruncle(node, r));
				node = tst_rbt_grandpa(node);
				/* 循环回去再看node的parent的情况 */
				/* 假如最后到根节点，这个时候根节点设置成红色。需要后面设置根节点为黑色 */
			}
			else
			{
				/* 叔叔是黑色。旋转树 */
				if (tst_rbt_is_rchild(node))
				{
					/* 父节点是左孩子，自己是右孩子，这个时候就是自己，父亲，祖父，叔叔连成闭合图形是菱形 */
					node = tst_rbt_parent(node);
					tst_rbt_rotate_left(root, node, sen);
				}
				tst_rbt_set_red(tst_rbt_grandpa(node));
				tst_rbt_set_black(tst_rbt_parent(node));
				tst_rbt_rotate_right(root, tst_rbt_grandpa(node), sen);
				/* 旋转之后就ok，循环结束 */
			}
		}
		else
		{	
			/* 父节点是祖父的右孩子，与上面是左孩子的操作相反就好。 */
			if (tst_rbt_is_red(tst_rbt_lruncle(node,l)))
			{	
				/* 叔叔是红色。调整颜色 */
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
	
	/* 二叉树的删除 */
	
	/* 找到要删除的节点。 */
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
		/* node的左右孩子都不为空，那么从右子树中找到key最小的节点，交换node和这个点，再删除node  */
		temp = tst_rbt_min_node(node->rchild, sentinel);
		if (temp->lchild == sentinel)
		{	
			/* 既然是最小的节点，一定进入这个分支，如果还有左孩子，temp肯定不是最小的 */
			subt = temp->rchild;
		}
		else
		{
			subt = temp->lchild;
		}
	}
	/* 如果要删除的点是根节点，这种情况只会是fd1，fd2中的一种 */
	if (temp == *root)
	{
		*root = subt;
		tst_rbt_set_black(subt);
		tst_rbt_node_reset(node);
		return;
	}

	unsigned char isRed = tst_rbt_is_red(temp);

	/* 把找到的节点移出树外。孩子上提  */
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
		/* 如果要删除的点就是node，那么node已经被移出树外 */
		subt->parent = temp->parent;
	}
	else
	{
		/* 如果要删除的点不是node，而是右子树中最小的节点 */

		if (node == tst_rbt_parent(temp))
		{
			/*如果node是temp的父节点，那么，subt的父节点还是temp，但是如果subt是sentinel，那么sentinel一开始parent是NULL */
			subt->parent = temp;
		}
		else
		{
			/* 如果不是，那么subt的父节点该是temp的父节点 */
			subt->parent = temp->parent;
		}

		temp->parent = node->parent;
		temp->lchild = node->lchild;
		temp->rchild = node->rchild;
		tst_rbt_copy_color(temp, node);

		if (node == *root)
		{
			/* 如果node是根，设置根为找到的节点 */
			*root = temp;
		}
		else
		{
			/* 把找到的点替换node  */
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


	/* 重新平衡红黑树 */
	while (subt != *root && tst_rbt_is_black(subt))
	{
		if (tst_rbt_is_lchild(subt))
		{
			w = tst_rbt_parent(subt)->rchild;
			/*复杂情况1：
			*兄弟是红色，那么父节点，兄弟的孩子都是黑色。交换兄弟与父亲的颜色
			*然后左旋。转换情况为要删除的点的兄弟是黑色。
			*/
			if (tst_rbt_is_red(w))//w是红色。则w的parent，child必然是黑色
			{
				tst_rbt_set_red(tst_rbt_parent(subt));
				tst_rbt_set_black(w);
				tst_rbt_rotate_left(root, tst_rbt_parent(subt), sentinel);
				w = tst_rbt_parent(subt)->rchild;//转化为subt的兄弟是黑色的情况
			}
			/*复杂情况2：
			*如果要删除的点的兄弟不是红色，并且兄弟的左右孩子都是黑色
			*那么把兄弟染成红色，再看父节点。如果是红色，跳出循环，最后染成黑色，ok
			*如果父节点是黑色，那么又回到最原始的问题（情况1234都可能）
			*/
			if (tst_rbt_is_black(w->lchild) && tst_rbt_is_black(w->rchild))
			{
				tst_rbt_set_red(w);
				subt = tst_rbt_parent(subt);
			}
			else
			{
				/* 复杂情况3：兄弟节点有红色孩子
				*如果兄弟的远侄子是黑色，那么肯定近亲侄子是红色。
				*最终目的是把远侄子变成红色，转换成下一种情况，可以最终解决问题。
				*/

				if (tst_rbt_is_black(w->rchild))
				{
					tst_rbt_set_black(w->lchild);
					tst_rbt_set_red(w);
					tst_rbt_rotate_right(root, w, sentinel);
					w = tst_rbt_parent(subt)->rchild;
				}

				/* 复杂情况4：
				*如果远侄子是红色，直接把远侄子设为黑色，交换父亲与兄弟颜色
				*最终选择合适的旋转方向旋转子树。达到平衡。
				*/
				tst_rbt_copy_color(w, tst_rbt_parent(subt));
				tst_rbt_set_black(tst_rbt_parent(subt));
				tst_rbt_set_black(w->rchild);
				tst_rbt_rotate_left(root, tst_rbt_parent(subt), sentinel);
				subt = *root;/* 结束循环，同时方便后续设置根节点为黑色 */
			}

		}
		else
		{
			/* 与上面，删除点是父亲的左孩子相似，只不过，旋转树的时候方向与上面情况相反 */
			w = tst_rbt_parent(subt)->lchild;
			if (tst_rbt_is_red(w))/* w是红色。w的parent，child必然是黑色 */
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
**    如下图：20 这个节点左旋 或者 右旋
**                                                                                   
**           30                  30    		          10                   10        
**           / \                 / \		          / \                  / \       
**          20  31    左旋      22   31		         9   20      左旋     9   22     
**         / \      ------->   / \          或者        / \     ------->     / \      
**       18  22    <-------   20  23                  18   22  <--------   20   23  
**           / \      右旋   / \   			               / \   右旋     / \     	
**         21   23          18  21			              21  23        18   21   	
**         										     					  			   
***************************************************************************************/
static tst_rbt_inline void 
tst_rbt_rotate_left(tst_rbtnode** root, tst_rbtnode* node, tst_rbtnode* sentinel)
{
	tst_rbtnode* temp;

	temp = node->rchild;
	node->rchild = temp->lchild;	//相当于把21变成20的右孩子

	if (temp->lchild != sentinel)
	{
		temp->lchild->parent = node;//21位置改变之后，重新设置他的parent
	}
	if (node == *root)
	{
		*root = temp;				//如果node是根节点。则temp是根节点
	}
	else if (node == tst_rbt_parent(node)->lchild )
	{
		tst_rbt_parent(node)->lchild = temp;//第一图，node在父节点的左孩子节点
	}
	else
	{
		tst_rbt_parent(node)->rchild = temp;//第二图，node在父节点的右孩子节点
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

