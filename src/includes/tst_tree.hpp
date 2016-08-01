#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "tst_rbtree.h"

	/*相当于层次遍历了吧。 */
	void dsprbttree(tst_rbtnode* root, tst_rbtnode* sentinel);
	void dspavltree(tst_rbtnode* root, tst_rbtnode* sentinel = NULL);

	int treenodecount(tst_rbtnode* root, tst_rbtnode* sentinel);
	int treehigh(tst_rbtnode* root, tst_rbtnode* sentinel);
	int treehigh_s(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*遍历-递归 */
	void middsptree(tst_rbtnode* root, tst_rbtnode* sentinel);
	void predsptree(tst_rbtnode* root, tst_rbtnode* sentinel);
	void aftdsptree(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*遍历-栈 */
	void predsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel);
	void predsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel);

	void middsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel);
	void middsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel);

	void middsptree_s_s(tst_rbtnode* root, tst_rbtnode* sentinel);

	void aftdsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel);
	void aftdsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*镜像 */
	void mirror(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*判断树是否对称，红黑树不可能是对称(symmetry)的。。 */
	bool judgesym(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*红黑树转换为双向链表 */
	tst_rbtnode* changetolink(tst_rbtnode* root, tst_rbtnode* sentinel);

	void destoytree(tst_rbtnode* root, tst_rbtnode* sentinel);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_MAIN_H_#pragma once
