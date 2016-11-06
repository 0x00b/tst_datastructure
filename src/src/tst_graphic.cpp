#include "tst_graphic.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tst_queue.hpp"

TstGraphicMtx::TstGraphicMtx() :
	m_pVertex(NULL),
	m_pAdcy_mtx(NULL),
	m_pVisited(NULL),
	m_nMax(0),
	m_bDir(false)
{

}

TstGraphicMtx::~TstGraphicMtx()
{
	delete[] m_pVisited;
	delete[] m_pVertex;
	if (NULL != m_pAdcy_mtx)
	{
		for (nodepos i = 0; i < m_nMax; i++)
		{
			delete[] m_pAdcy_mtx[i];

		}
		delete[] m_pAdcy_mtx;
	}
}

void TstGraphicMtx::create()
{
	std::cout << "input number of node£º" ;
	std::cin >> m_nMax;

	std::cout << "is directed(0(no)/1(yes))£º" ;
	std::cin >> m_bDir;

	m_pVisited = new bool[m_nMax] {};

	m_pVertex = new char[m_nMax] {};

	m_pAdcy_mtx = new nodepos*[m_nMax];
	for (nodepos i = 0; i < m_nMax; i++)
	{
		m_pAdcy_mtx[i] = new nodepos[m_nMax];
		for (nodepos j = 0; j < m_nMax; j++)
		{
			m_pAdcy_mtx[i][j] = M_INFINITY;
		}
	}
	
	std::cout << "per node's name(one char)£º" ;
	for (nodepos i = 0; i < m_nMax; i++)
	{
		std::cin >> m_pVertex[i];
	}

	std::cout << "number of edge£º";
	std::cin >> m_nEdgeNum;

	std::cout << "edges£º" << std::endl;
	char cTempStart = 0;
	char cTempEnd = 0;
	nodepos nPosStart = -1;
	nodepos nPosEnd = -1;
	nodepos nWeight;
	for (unsigned i = 0; i < m_nEdgeNum; i++)
	{
		std::cin >> cTempStart >> cTempEnd >> nWeight;
		nPosStart = FindNode(cTempStart);
		if (-1 == nPosStart)
		{
			std::cout << "have not the start node£¡" << std::endl;
		}
		else
		{
			nPosEnd = FindNode(cTempEnd);
			if (-1 == nPosEnd)
			{
				std::cout << "have not the end node£¡" << std::endl;
			}
			else 
			{
				m_pAdcy_mtx[nPosStart][nPosEnd] = nWeight;
				if (!m_bDir)
				{
					m_pAdcy_mtx[nPosEnd][nPosStart] = nWeight;
				}
			}
		}
	}
}
TstGraphicMtx::nodepos TstGraphicMtx::FindNode(char node)
{
	for (nodepos i = 0; i < m_nMax; i++)
	{
		if (node == m_pVertex[i])
		{
			return i;
		}
	}
	return -1;
}

void TstGraphicMtx::TraverseDepthFirst()
{
	std::cout << "Traverse Depth-First£º" << std::endl;

	memset(m_pVisited, 0x00, m_nMax * sizeof(bool));

	for (nodepos i = 0; i < m_nMax; i++)
	{
		if (!m_pVisited[i])
		{
			DepthFirst(i);
		}
	}

	std::cout << std::endl;
}
void TstGraphicMtx::DepthFirst(nodepos pos)
{
	m_pVisited[pos] = true;
	visit(pos);
	for (nodepos i = 0; i < m_nMax; i++)
	{
		if (M_INFINITY != m_pAdcy_mtx[pos][i] && (!m_pVisited[i]))
		{
			DepthFirst(i);
		}
	}
}
void TstGraphicMtx::TraverseBreadthFirst()
{
	std::cout << "Traverse Breadth-First£º" << std::endl;

	memset(m_pVisited, 0x00, m_nMax * sizeof(bool));
	nodepos ndp;
	TstQueue<nodepos> tq;
	for (nodepos i = 0; i < m_nMax; i++)
	{
		if (!m_pVisited[i])
		{
			tq.push(i);
			m_pVisited[i] = true;
			visit(i);
			while (!tq.empty())
			{
				ndp = tq.front();
				tq.pop();
				for (nodepos j = 0; j < m_nMax; j++)
				{
					if ((M_INFINITY != m_pAdcy_mtx[ndp][j]) && (!m_pVisited[j]))
					{
						m_pVisited[j] = true;
						visit(j);
						tq.push(j);
					}
				}
			}
		}
	}

	std::cout << std::endl;
}

void TstGraphicMtx::visit(nodepos nPos)
{
	std::cout << "->" << m_pVertex[nPos];
}

void TstGraphicMtx::DispGraphic()
{
	for (nodepos i = 0; i < m_nMax; i++)
	{
		std::cout << "\t" << m_pVertex[i];
	}
	std::cout << std::endl;
	for (nodepos i = 0; i < m_nMax; i++)
	{
		std::cout << m_pVertex[i];
		for (nodepos j = 0; j < m_nMax; j++)
		{
			if (M_INFINITY == m_pAdcy_mtx[i][j])
			{
				std::cout << "\t¡Þ";
			}
			else
			{
				std::cout << "\t" << m_pAdcy_mtx[i][j];
			}
		}
		std::cout<<std::endl;
	}

}


/*********************  TstGraphicLink  ***********************/

TstGraphicLink::TstGraphicLink()
{
}

TstGraphicLink::~TstGraphicLink()
{
}
