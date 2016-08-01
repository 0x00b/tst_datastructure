#ifndef _TST_GRAPHIC_H_
#define _TST_GRAPHIC_H_

#include <limits.h>

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



#endif //_TST_GRAPHIC_H_
