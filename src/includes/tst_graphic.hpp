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
	void TraverseDepthFirst();	/* 深度优先 */
	void DepthFirst(nodepos nPos);
	void TraverseBreadthFirst();/* 广度优先 */
	void visit(nodepos nPos);
	nodepos FindNode(char node);

public:

private:
	bool*		m_pVisited;
	char*		m_pVertex;
	int**		m_pAdcy_mtx;	/* adjacency_matrix 邻接矩阵*/
	int			m_nMax;			/* 最大节点数 */
	unsigned	m_nEdgeNum;		/* 边数量 */
	bool		m_bDir;			/* 是否有向图 */
};



#endif //_TST_GRAPHIC_H_
