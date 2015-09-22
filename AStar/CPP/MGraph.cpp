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

// ת������� Id ����������
void MGraph::convIdToXY(int vertId, int* x, int* y)
{
	*y = vertId / m_xCount;
	*x = vertId - *y * m_xCount;
}

int MGraph::convXYToVertId(int x, int y)
{
	return (y * m_xCount + x);
}

// �Ƿ����赲����
bool MGraph::isInStopPt(int nx, int ny)
{
	if (nx >= 0 && nx < m_xCount
		&& ny >= 0 && ny < m_yCount)
	{
		int index = ny * m_xCount + nx;
		if (m_id2StopPtMap[index])			// ������赲��
		{
			return true;
		}
	}

	return false;
}

/**
* @brief �ھӸ��ӳɱ�
* @param vertId ��ʼ���� Id
* @Param neighborVertId �ھӶ��� Id
*	5	6	7
*	4		0
*	3	2	1
*/
float MGraph::adjacentCost(int vertId, int neighborVertId)
{
	int x, y;
	int xNeighbor, yNeighbor;
	float neighborCost = std::numeric_limits<float>::max();			// Ĭ�������ֵ
	const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	//const float cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };
	const float cost[8] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	if (vertId == neighborVertId)		// ������Լ����ͷ��� 0
	{
		return 0;
	}

	convIdToXY(neighborVertId, &xNeighbor, &yNeighbor);
	if (isInStopPt(xNeighbor, yNeighbor))		// ����ھ����赲����
	{
		return neighborCost;
	}

	convIdToXY(vertId, &x, &y);
	if (std::abs((long)(xNeighbor - x)) > 1 || std::abs((long)(yNeighbor - y)) > 1)	// ������� 1 ����˵���м��м��������ֱ�ӵ���
	{
		return neighborCost;
	}

	for (int i = 0; i<8; ++i)
	{
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (convXYToVertId(nx, ny) == neighborVertId)		// ����������ھ�
		{
			// �϶������赲���У���Ϊ������赲���У������Ѿ��ж���
			if (isHorizontalOrVertical(vertId, neighborVertId))		// �������ˮƽ���ߴ�ֱ����б��
			{
				neighborCost = cost[i];
			}
			else
			{
				// ��Ҫ�ж�б���ϵ���һ��б�ߵ����������Ƿ����赲��
				if (!isInStopPt(x, yNeighbor) && !isInStopPt(xNeighbor, y))		// ����Խ����ϵ��������Ӷ������赲��
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

	if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||		// ˮƽ
		(std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1) ||		// ��ֱ
		(std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 1))			// б��
	{
		return true;
	}

	return false;
}