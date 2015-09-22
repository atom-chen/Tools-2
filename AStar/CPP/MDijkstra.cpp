#include "MGraph.h"

#include <numeric>
#include <stdexcept>
#include <list>

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

std::list<Vertex*> MGraph::buildPath(Vertex *endVert)
{
	std::list<Vertex*> pathList;

	Vertex *vert = endVert;
	while (vert != nullptr) 
	{
		pathList.push_front(vert);
		vert = vert->m_nearestVert;
	}
	pathList.push_front(m_startVert);		// ������Ķ���Ž�ȥ
	return pathList;
}

void MGraph::initializeNodes(unsigned int startId, unsigned int endId)
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

std::list<Vertex*> MGraph::getShortestPath(unsigned int startId, unsigned int endId)
{
	initializeNodes(startId, endId);

	int v, w, k;
	float min;
	int nVer = m_vertsCount;
	Vertex* pVert = nullptr;

	// ��ʼ������
	for (v = 0; v < nVer; ++v)
	{
		m_startVert->m_state = State::Unknown;    // ȫ�������ʼ��Ϊδ֪�Զ�·��״̬
		pVert = m_verts[v];
		pVert->m_distance = adjacentCost(startId, v); //����V0�������ߵĶ������Ȩֵ
		pVert->m_nearestVert = nullptr;    // ��ʼ��·������pΪ0
	}

	m_startVert->m_distance = 0;    // V0��V0·��Ϊ0
	m_startVert->m_state = State::Closed;    // final[W]=1��ʾV0��V0����Ҫ��·��

	// ��ʼ��ѭ����ÿ�����V0��ĳ��V��������·��
	for (v = 1; v < nVer; ++v)
	{
		min = std::numeric_limits<float>::max();    // ��ǰ��֪��V0�����������
		for (w = 0; w < nVer; ++w) // Ѱ����V0����Ķ���
		{
			pVert = m_verts[w];
			if (pVert->m_state != State::Closed && pVert->m_distance < min)
			{
				min = pVert->m_distance; // w������V0�������
				k = w;
			}
		}

		// ע����ʼ����͵ڶ�������֮����û�� m_nearestVert �������Ҫ�ֹ�����һ������ŵ�·���б���ȥ
		pVert = m_verts[k];
		pVert->m_state = State::Closed; // ��Ŀǰ�ҵ�������Ķ�����Ϊ1

		for (w = 0; w < nVer; ++w) // ������ǰ���·������
		{
			pVert = m_verts[w];
			// �������V�����·������������·���ĳ��ȶ̵Ļ�
			if (pVert->m_state != State::Closed && (min + adjacentCost(k, w) < pVert->m_distance))
			{
				// ˵���ҵ�����̵�·�����޸�D[w] �� p[w]
				pVert->m_distance = min + adjacentCost(k, w); // �޸ĵ�ǰ·������
				pVert->m_nearestVert = m_verts[k];
			}
		}

		if (k == endId)			// ������ҵ�
		{
			break;
		}
	}

	return buildPath(m_endVert);
}