#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

#include "tst_rbtree.h"

	/*�൱�ڲ�α����˰ɡ� */
	void dsprbttree(tst_rbtnode* root, tst_rbtnode* sentinel);
	void dspavltree(tst_rbtnode* root, tst_rbtnode* sentinel = NULL);

	int treenodecount(tst_rbtnode* root, tst_rbtnode* sentinel);
	int treehigh(tst_rbtnode* root, tst_rbtnode* sentinel);
	int treehigh_s(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*����-�ݹ� */
	void middsptree(tst_rbtnode* root, tst_rbtnode* sentinel);
	void predsptree(tst_rbtnode* root, tst_rbtnode* sentinel);
	void aftdsptree(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*����-ջ */
	void predsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel);
	void predsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel);

	void middsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel);
	void middsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel);

	void middsptree_s_s(tst_rbtnode* root, tst_rbtnode* sentinel);

	void aftdsptree_s_1(tst_rbtnode* root, tst_rbtnode* sentinel);
	void aftdsptree_s_2(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*���� */
	void mirror(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*�ж����Ƿ�Գƣ�������������ǶԳ�(symmetry)�ġ��� */
	bool judgesym(tst_rbtnode* root, tst_rbtnode* sentinel);

	/*�����ת��Ϊ˫������ */
	tst_rbtnode* changetolink(tst_rbtnode* root, tst_rbtnode* sentinel);

	void destoytree(tst_rbtnode* root, tst_rbtnode* sentinel);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_MAIN_H_#pragma once
