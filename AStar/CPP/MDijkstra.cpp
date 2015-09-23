#include "MGraph.h"

#include <numeric>
#include <stdexcept>
#include <list>

std::list<Vertex*>& MGraph::getPath()
{
	return m_pathList;
}

bool MGraph::checkFail(Vertex *endVert)
{
	if (!endVert->m_nearestVert)	// ����յ�û��ǰ��ָ��Ľڵ�
	{
		if (!isNeighbor(m_startVert->m_id, m_endVert->m_id))		// ��������ھӣ���Ȼʧ��
		{
			return true;
		}
		else if (isSlashNeighbor(m_startVert->m_id, m_endVert->m_id))		// ����ǶԽ��ھ�
		{
			if (isBackSlashStopPoint(m_startVert->m_id, m_endVert->m_id))
			{
				return true;
			}
		}
	}

	return false;
}

std::list<Vertex*>& MGraph::buildPath(Vertex *endVert)
{
	Vertex *vert = endVert;
	while (vert != nullptr)
	{
		m_pathList.push_front(vert);
		vert = vert->m_nearestVert;
	}
	m_pathList.push_front(m_startVert);		// ������Ķ���Ž�ȥ

	return m_pathList;
}

void MGraph::initVerts(unsigned int startId, unsigned int endId)
{
	m_startVert = m_endVert = nullptr;

	for (auto pVert : m_verts)
	{
		pVert->reset();

		if (pVert->m_id == startId) 
		{
			m_startVert = pVert;
		}
		else if (pVert->m_id == endId) 
		{
			m_endVert = pVert;
		}

		if (m_startVert != nullptr && m_endVert != nullptr)			// ������ҵ����˳�
		{
			break;
		}
	}

	if (m_startVert == nullptr || m_endVert == nullptr) 
	{
		throw std::runtime_error("Failed to find the start/end node(s)!");
	}

	m_startVert->m_distance = 0;
}

void MGraph::resetAllVerts(unsigned int startId)
{
	Vertex* pVert = nullptr;
	// ��ʼ������
	for (int vertIdx = 0; vertIdx < m_vertsCount; ++vertIdx)
	{
		m_startVert->m_state = State::Unknown;    // ȫ�������ʼ��Ϊδ֪�Զ�·��״̬
		pVert = m_verts[vertIdx];
		pVert->m_distance = adjacentCost(startId, vertIdx); //���� startId �������ߵĶ������Ȩֵ
		pVert->m_nearestVert = nullptr;    // ��ʼ��·����ǰһ������
	}

	m_startVert->m_distance = 0;    //  startId �� startId ·��Ϊ0
	m_startVert->m_state = State::Closed;    // m_startVert->m_state ��ʾ startId �� startId ����Ҫ��·�����Ѿ���ӵ�ȷ�϶�������
}

bool MGraph::findNextClosedVert(float& minDist, int& minIdx)
{
	Vertex* pVert = nullptr;
	int neighborVertIdx = 0;
	minDist = std::numeric_limits<float>::max();    // ��ǰ��֪�� startId �����������
	bool bFindNextClosedVert = false;
	for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // Ѱ���� startId ����Ķ���
	{
		pVert = m_verts[neighborVertIdx];
		if (pVert->m_state != State::Closed && pVert->m_distance < minDist)
		{
			minDist = pVert->m_distance; // w������ startId �������
			minIdx = neighborVertIdx;
			bFindNextClosedVert = true;				// ˵�����ҵ���
		}
	}

	return bFindNextClosedVert;
}

void MGraph::modifyVertsDist(float& minDist, int& minIdx)
{
	int neighborVertIdx = 0;
	Vertex* pVert = nullptr;

	for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // ������ǰ���·������
	{
		pVert = m_verts[neighborVertIdx];
		// �������V�����·������������·���ĳ��ȶ̵Ļ�
		if (pVert->m_state != State::Closed && (minDist + adjacentCost(minIdx, neighborVertIdx) < pVert->m_distance))
		{
			// ˵���ҵ�����̵�·�����޸�D[w] �� p[w]
			pVert->m_distance = minDist + adjacentCost(minIdx, neighborVertIdx); // �޸ĵ�ǰ·������
			pVert->m_nearestVert = m_verts[minIdx];
		}
	}
}

std::list<Vertex*>& MGraph::getShortestPath(unsigned int startId, unsigned int endId)
{
	m_pathList.clear();

	initVerts(startId, endId);

	int openVertIdx = 0;		// ��δȷ����ӵ������еĶ������������
	int neighborVertIdx = 0;
	int minIdx = 0;
	float minDist = 0;
	Vertex* pVert = nullptr;
	bool bFindShortestPath = false;

	resetAllVerts(startId);

	// �ܹ��� nVerts �����㣬�� startId ���Ѿ�ȷ�ϣ�ֻ��Ҫȷ��ʣ�µ� nVerts - 1 �Ϳ�����
	for (openVertIdx = 1; openVertIdx < m_vertsCount; ++openVertIdx)
	{
		if (findNextClosedVert(minDist, minIdx))	// ������ҵ�����һ����̵�δȷ�ϵ�����
		{
			// ע����ʼ����͵ڶ�������֮����û�� m_nearestVert �������Ҫ�ֹ�����һ������ŵ�·���б���ȥ
			pVert = m_verts[minIdx];
			pVert->m_state = State::Closed; // ��Ŀǰ�ҵ�������Ķ�����Ϊ State::Closed 

			modifyVertsDist(minDist, minIdx);
		}
		else				// ����Ҳ�����һ����С�Ķ�����������ֱ���˳��ɣ�û����̾���
		{
			bFindShortestPath = false;
			break;
		}

		if (minIdx == endId)			// ������ҵ�
		{
			bFindShortestPath = true;
			break;
		}
	}

	if (bFindShortestPath)
	{
		return buildPath(m_endVert);
	}
	else
	{
		return m_pathList;
	}
}