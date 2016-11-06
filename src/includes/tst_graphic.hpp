#ifndef _TST_GRAPHIC_H_
#define _TST_GRAPHIC_H_

#include <limits.h>
#include <vector>
/********************************************************************
 * �����ڽӾ�������ʾͼ 
 * �ŵ㣺
 * ȱ�㣺
 ********************************************************************/
class TstGraphicMtx
{
public:
	typedef int nodepos;
	static const int M_INFINITY = INT_MAX;
	TstGraphicMtx();
	~TstGraphicMtx();
	void create();
	void DispGraphic();
	void TraverseDepthFirst();	/* ������� */
	void DepthFirst(nodepos nPos);
	void TraverseBreadthFirst();/* ������� */
	void visit(nodepos nPos);
	nodepos FindNode(char node);

public:

private:
	
	bool*		m_pVisited;
	char*		m_pVertex;
	int**		m_pAdcy_mtx;	/* adjacency_matrix �ڽӾ���*/
	int			m_nMax;			/* ���ڵ��� */
	unsigned	m_nEdgeNum;		/* ������ */
	bool		m_bDir;			/* �Ƿ�����ͼ */
};

/********************************************************************
 * �����ڽӱ�����ʾͼ 
 * �ŵ㣺
 * ȱ�㣺
 ********************************************************************/

class TstGraphicLink
{
public:
	typedef int nodepos;

	TstGraphicLink();
	~TstGraphicLink();

private:
	//TstList<nodepos>* tl;
};

#endif //_TST_GRAPHIC_H_
