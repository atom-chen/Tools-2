#include "MGraph.h"

void Vertex::reset()
{
	//m_id = 0;
	m_state = State::Unknown;
	m_nearestVert = nullptr;
	m_distance = std::numeric_limits<float>::max();
}

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

Vertex* MGraph::getVert(int id)
{
	if (id < m_verts.size())
	{
		return m_verts[id];
	}

	return nullptr;
}

size_t MGraph::getVertsCount()
{
	return m_verts.size();
}

void MGraph::init(int xCount, int yCount)
{
	m_xCount = xCount;
	m_yCount = yCount;
	m_vertsCount = m_xCount * m_yCount;

	int idx = 0;
	Vertex* pVertex = nullptr;

	for (idx = 0; idx < m_vertsCount; ++idx)
	{
		pVertex = new Vertex();
		m_verts.push_back(pVertex);
		pVertex->reset();
		pVertex->m_id = idx;
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
		if (m_id2StopPtMap[index])			// 如果有阻挡点
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
	//const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };
	const float cost[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	if (vertId == neighborVertId)		// 如果是自己，就返回 0
	{
		return 0;
	}

	convIdToXY(neighborVertId, &xNeighbor, &yNeighbor);
	if (isInStopPt(xNeighbor, yNeighbor))		// 如果邻居在阻挡点中
	{
		return neighborCost;
	}

	convIdToXY(vertId, &x, &y);
	if (std::abs((long)(xNeighbor - x)) > 1 || std::abs((long)(yNeighbor - y)) > 1)	// 如果相差不是 1 ，就说明中间有间隔，不能直接到达
	{
		return neighborCost;
	}

	for (int i = 0; i<8; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (convXYToVertId(nx, ny) == neighborVertId)		// 如果正好是邻居
		{
			// 肯定不在阻挡点中，因为如果在阻挡点中，上面已经判断了
			if (isHorizontalOrVertical(vertId, neighborVertId))		// 如果不是水平或者垂直，是斜线
			{
				neighborCost = cost[i];
			}
			else
			{
				// 需要判断斜线上的另一个斜线的两个格子是否是阻挡点
				if (!isInStopPt(x, yNeighbor) && !isInStopPt(xNeighbor, y))		// 如果对角线上的两个格子都不是阻挡点
				{
					neighborCost = cost[i];
				}
			}

			break;
		}
	}

	return neighborCost;
}

void MGraph::addStopPoint(int nx, int ny, StopPoint* pStopPoint)
{
	int vertId = convXYToVertId(nx, ny);
	m_id2StopPtMap[vertId] = pStopPoint;
}

bool MGraph::isHorizontalOrVertical(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convIdToXY(vertId, &x, &y);
	convIdToXY(neighborVertId, &xNeighbor, &yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||
		(std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1))
	{
		return true;
	}

	return false;
}

bool MGraph::isNeighbor(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convIdToXY(vertId, &x, &y);
	convIdToXY(neighborVertId, &xNeighbor, &yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||		// 水平
		(std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1) ||		// 垂直
		(std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 1))			// 斜线
	{
		return true;
	}

	return false;
}