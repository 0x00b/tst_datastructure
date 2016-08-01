/*
** tst_rbtree.h
** create by lj
*/

#ifndef _TST_RBTREE_H_
#define _TST_RBTREE_H_

#if 0
#define tst_rbt_inline inline 
#else
#define tst_rbt_inline
#endif

typedef struct tst_rbtnode_t tst_rbtnode;

/* 树的节点结构 */
struct tst_rbtnode_t
{
	unsigned int	key;
	tst_rbtnode*	parent;
	tst_rbtnode*	lchild;
	tst_rbtnode*	rchild;
	int				height;
	unsigned char	color;
	unsigned char*	data;

};


typedef struct tst_rbtree_t tst_rbtree;
typedef void(*tst_rbt_insert_func)(tst_rbtnode* root, tst_rbtnode* node, tst_rbtnode* sen);

/* 树结构 */
struct tst_rbtree_t
{
	tst_rbtnode*	root;
	tst_rbtnode*	sentinel;/* 哨兵 */
	tst_rbt_insert_func	insert;
};

/* define */
#define tst_rbt_is_leaf(tree, n)	((tree)->sentinel == (n))
#define tst_rbt_set_red(n)			((n)->color = 1)
#define tst_rbt_set_black(n)		((n)->color = 0)
#define tst_rbt_is_red(n)			((n)->color)
#define tst_rbt_is_black(n)			(!tst_rbt_is_red(n))
#define tst_rbt_copy_color(n1,n2)	((n1)->color = (n2)->color)
#define tst_rbt_parent(n)			((n)->parent)
#define tst_rbt_grandpa(n)			(((n)->parent)->parent)
#define tst_rbt_is_lchild(n)		((n)==(tst_rbt_parent(n)->lchild))
#define tst_rbt_is_rchild(n)		((n)==(tst_rbt_parent(n)->rchild))

#define tst_rbt_sibling(n)			(tst_rbt_parent(n)->lchild==(n)	\
									?tst_rbt_parent(n)->rchild	\
									:tst_rbt_parent(n)->lchild)

#define tst_rbt_lruncle(n,lr)			(tst_rbt_grandpa(n)->lr##child)

#define tst_rbt_uncle(n)			((tst_rbt_parent(n)==(tst_rbt_grandpa(n)->lchild))	\
									?(tst_rbt_grandpa(n)->rchild)				\
									:(tst_rbt_grandpa(n)->lchild))

#define tst_rbt_init(tree, psentinel, i)	\
do											\
{											\
	tst_rbt_set_black(psentinel);			\
	(tree)->root = psentinel;				\
	(tree)->sentinel = psentinel;			\
	(tree)->insert = i;						\
} while (0)

#define tst_rbt_node_init(node, nkey )		\
do											\
{											\
	memset(node, 0x00, sizeof(tst_rbtnode));\
	(node)->key = nkey;						\
	(node)->height = 1;						\
} while (0)

#define tst_rbt_node_reset(node) tst_rbt_node_init(node, 0)

/* 一些操作函数 */
void tst_rbt_insert_default(tst_rbtnode* parent, tst_rbtnode* node, tst_rbtnode* sentinel);
void tst_rbt_insert(tst_rbtree* tree, tst_rbtnode* node);
void tst_rbt_delete(tst_rbtree* tree, tst_rbtnode* node);
void tst_rbt_free(tst_rbtree* tree);

tst_rbtnode* tst_rbt_find(tst_rbtree* tree, tst_rbtnode* sentinel, unsigned int key);

tst_rbt_inline tst_rbtnode* tst_rbt_min_node(tst_rbtnode* node, tst_rbtnode* sentinel);

#endif