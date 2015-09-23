#include "MGraph.h"

void Vertex::reset()
{
	//m_id = 0;
	m_state = State::Unknown;
	m_nearestVert = nullptr;
	m_distance = std::numeric_limits<float>::max();
	m_bNeighborValid = false;
}

void Vertex::setNeighborVertsId(int* neighborVertIdArr, int len)
{
	m_vertsIdVec.clear();
	m_bNeighborValid = true;
	for (int idx = 0; idx < len; ++idx)
	{
		if (neighborVertIdArr[idx] != -1)
		{
			m_vertsIdVec.push_back(neighborVertIdArr[idx]);
		}
	}
}

MGraph::MGraph()
{

}

MGraph::~MGraph()
{
	for (auto pVert : m_vertsVec)
	{
		delete pVert;
	}
}


Vertex* MGraph::getVertexById(int vertId)
{
	if (vertId < m_vertsVec.size())
	{
		return m_vertsVec[vertId];
	}

	return nullptr;
}

const MGraph::VertVector& MGraph::getVertsVec() const
{
	return m_vertsVec;
}

size_t MGraph::getVertsCount()
{
	return m_vertsVec.size();
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
		m_vertsVec.push_back(pVertex);
		pVertex->reset();
		pVertex->m_id = idx;
	}
}

// 转换顶点的 Id 到顶点索引
void MGraph::convVertIdToXY(int vertId, int& x, int& y)
{
	y = vertId / m_xCount;
	x = vertId - y * m_xCount;
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

	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);
	if (isInStopPt(xNeighbor, yNeighbor))		// 如果邻居在阻挡点中
	{
		return neighborCost;
	}

	convVertIdToXY(vertId, x, y);
	if (std::abs((long)(xNeighbor - x)) > 1 || std::abs((long)(yNeighbor - y)) > 1)	// 如果相差不是 1 ，就说明中间有间隔，不能直接到达
	{
		return neighborCost;
	}

	int nx = 0;
	int ny = 0;

	for (int i = 0; i<8; ++i)
	{
		nx = x + dx[i];
		ny = y + dy[i];

		if (convXYToVertId(nx, ny) == neighborVertId)		// 如果正好是邻居
		{
			// 肯定不在阻挡点中，因为如果在阻挡点中，上面已经判断了
			if (isHorizontalOrVerticalNeighbor(vertId, neighborVertId))		// 如果是水平或者垂直，是斜线
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

	// 需要修改邻居是这个顶点的其它顶点的邻居
	if (!m_vertsVec[vertId]->m_bNeighborValid)
	{
		findNeighborVertIdArr(vertId);
		m_vertsVec[vertId]->setNeighborVertsId(m_neighborVertIdArr);
	}
	
	for (int neighborIdx = 0; neighborIdx < m_vertsVec[vertId]->m_vertsIdVec.size(); ++neighborIdx)
	{
		m_vertsVec[m_vertsVec[vertId]->m_vertsIdVec[neighborIdx]]->m_bNeighborValid = false;
	}
}

bool MGraph::isHorizontalOrVerticalNeighbor(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convVertIdToXY(vertId, x, y);
	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||
		(std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1))
	{
		return true;
	}

	return false;
}

bool MGraph::isHorizontalNeighbor(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convVertIdToXY(vertId, x, y);
	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0))
	{
		return true;
	}

	return false;
}

bool MGraph::isVerticalNeighbor(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convVertIdToXY(vertId, x, y);
	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1))
	{
		return true;
	}

	return false;
}

bool MGraph::isSlashNeighbor(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convVertIdToXY(vertId, x, y);
	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 1))			// 斜线
	{
		return true;
	}

	return false;
}

bool MGraph::isNeighbor(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convVertIdToXY(vertId, x, y);
	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||		// 水平
		(std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1) ||		// 垂直
		(std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 1))			// 斜线
	{
		return true;
	}

	return false;
}

bool MGraph::isBackSlashStopPoint(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	convVertIdToXY(vertId, x, y);
	convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	if (isInStopPt(x, yNeighbor) || isInStopPt(xNeighbor, y))
	{
		return true;
	}

	return false;
}

void MGraph::findNeighborVertIdArr(int vertId)
{
	int x, y;
	convVertIdToXY(vertId, x, y);

	const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

	int nx = 0;
	int ny = 0;

	// 遍历 8 个邻居顶点
	for (int i = 0; i < 8; ++i)
	{
		nx = x + dx[i];
		ny = y + dy[i];

		if (nx >= 0 && nx < m_xCount &&
			ny >= 0 && ny < m_yCount)		// 如果邻居顶点在范围内
		{
			if (!isInStopPt(nx, ny))		// 如果不在阻挡点内
			{
				m_neighborVertIdArr[i] = convXYToVertId(nx, ny);
			}
			else
			{
				m_neighborVertIdArr[i] = -1;
			}
		}
		else
		{
			m_neighborVertIdArr[i] = -1;
		}
	}
}