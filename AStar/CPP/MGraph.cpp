#include "MGraph.h"


MGraph::MGraph()
{

}

MGraph::~MGraph()
{
	for (auto pVert : m_verts)
	{
		delete pVert;
	}
}


Vertex* MGraph::getVertexById(int vertId)
{
	return m_verts[vertId];
}

const MGraph::VertVector& MGraph::getVerts() const
{
	return m_verts;
}

Vertex* MGraph::getOrAddVert(int id)
{
	Vertex *vert = m_verts[id];
	if (vert == nullptr)
	{
		vert = new Vertex();
		vert->m_id = id;

		m_verts[id] = vert;
	}

	return vert;
}

int MGraph::getVertsCount()
{
	return m_verts.size();
}

void MGraph::init(int xCount, int yCount)
{
	m_xCount = xCount;
	m_yCount = yCount;
	m_vertsCount = m_xCount * m_yCount;

	int idx = 0;

	for (idx = 0; idx < m_vertsCount; ++idx)
	{
		getOrAddVert(idx);
	}
}

// 转换顶点的 Id 到顶点索引
void MGraph::convIdToXY(int vertId, int* x, int* y)
{
	*y = vertId / m_xCount;
	*x = vertId - *y * m_xCount;
}

int MGraph::convXYToVertId(int x, int y)
{
	return (y * m_xCount + x);
}

// 是否在阻挡点内
bool MGraph::isInStopPt(int nx, int ny)
{
	if (nx >= 0 && nx < m_xCount
		&& ny >= 0 && ny < m_yCount)
	{
		int index = ny * m_xCount + nx;
		if (!m_id2StopPtMap[index])			// 如果有阻挡点
		{
			return true;
		}
	}

	return false;
}

/**
* @brief 邻居格子成本
* @param vertId 起始顶点 Id
* @Param neighborVertId 邻居顶点 Id
*	5	6	7
*	4		0
*	3	2	1
*/
float MGraph::adjacentCost(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	float neighborCost = std::numeric_limits<float>::max();			// 默认是最大值
	const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };

	if (vertId == neighborVertId)
	{
		return 0;
	}

	convIdToXY(neighborVertId, &xNeighbor, &yNeighbor);
	if (isInStopPt(xNeighbor, yNeighbor))		// 如果邻居在阻挡点中
	{
		return neighborCost;
	}

	convIdToXY(vertId, &x, &y);
	if (std::abs((long)(xNeighbor, x)) > 1 || std::abs((long)(yNeighbor, y)) > 1)	// 如果相差不是 1 ，就说明不能直接到达
	{
		return neighborCost;
	}

	for (int i = 0; i<8; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (convXYToVertId(nx, ny) == neighborVertId)		// 如果正好是邻居
		{
			if (!isInStopPt(nx, ny))		// 如果不在阻挡点中
			{
				neighborCost = cost[i];
			}
		}
	}

	return neighborCost;
}