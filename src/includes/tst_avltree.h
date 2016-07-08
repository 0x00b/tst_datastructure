#ifndef _TST_AVLTREE_H_
#define _TST_AVLTREE_H_

#include "tst_rbtree.h"
#include <stdio.h>

typedef tst_rbtnode tst_avlnode;

#define tst_avl_node_init		tst_rbt_node_init
#define tst_avl_min_node(node)	tst_rbt_min_node((node),NULL)
#define tst_avl_pa				1
#define tst_avl_set_pa(n , p)	(tst_avl_pa && (NULL != (n)) && ((n)->parent = (p)))


tst_avlnode* tst_avl_max_node(tst_avlnode* node);

tst_avlnode* tst_avl_insert(tst_avlnode** root, tst_avlnode* node);
void tst_avl_delete_beta(tst_avlnode** root, tst_avlnode* node);
void tst_avl_delete(tst_avlnode** root, tst_avlnode* node);

tst_avlnode* tst_avl_rotate_left(tst_avlnode** node);
tst_avlnode* tst_avl_rotate_right(tst_avlnode** node);

#endif
