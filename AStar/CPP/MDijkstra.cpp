#include "MGraph.h"

#include <numeric>
#include <stdexcept>
#include <list>

std::list<Vertex*>& MGraph::getPath()
{
	return m_pathList;
}

//bool MGraph::checkFail(Vertex *endVert)
//{
//	if (!endVert->m_nearestVert)	// ����յ�û��ǰ��ָ��Ľڵ�
//	{
//		if (!isNeighbor(m_startVert->m_id, m_endVert->m_id))		// ��������ھӣ���Ȼʧ��
//		{
//			return true;
//		}
//		else if (isSlashNeighbor(m_startVert->m_id, m_endVert->m_id))		// ����ǶԽ��ھ�
//		{
//			if (isBackSlashStopPoint(m_startVert->m_id, m_endVert->m_id))
//			{
//				return true;
//			}
//		}
//	}
//
//	return false;
//}

void MGraph::buildPath(Vertex *endVert)
{
	Vertex *vert = endVert;
	while (vert != nullptr)
	{
		m_pathList.push_front(vert);
		vert = vert->m_nearestVert;
	}
	m_pathList.push_front(m_startVert);		// ������Ķ���Ž�ȥ

	//return m_pathList;
}

void MGraph::initVerts(unsigned int startId, unsigned int endId)
{
	m_startVert = nullptr;
	m_endVert = nullptr;

	int nx = 0;
	int ny = 0;

	convVertIdToXY(startId, nx, ny);
	if (nx >= 0 && nx < m_xCount
		&& ny >= 0 && ny < m_yCount)
	{
		m_startVert = m_vertsVec[startId];
	}

	convVertIdToXY(endId, nx, ny);
	if (nx >= 0 && nx < m_xCount
		&& ny >= 0 && ny < m_yCount)
	{
		m_endVert = m_vertsVec[endId];
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
		pVert = m_vertsVec[vertIdx];
		pVert->m_distance = adjacentCost(startId, vertIdx); //���� startId �������ߵĶ������Ȩֵ
		pVert->m_nearestVert = nullptr;    // ��ʼ��·����ǰһ������
	}

	m_startVert->m_distance = 0;    //  startId �� startId ·��Ϊ0
	m_startVert->m_state = State::Closed;    // m_startVert->m_state ��ʾ startId �� startId ����Ҫ��·�����Ѿ����ӵ�ȷ�϶�������
}

bool MGraph::findNextClosedVert(float& minDist, int& minIdx, std::vector<int>& closedVec)
{
	Vertex* pVert = nullptr;
	int closedIdx = 0;
	int neighborVertIdx = 0;
	minDist = std::numeric_limits<float>::max();    // ��ǰ��֪�� startId �����������
	bool bFindNextClosedVert = false;
	// �������ж��㣬�������·�������Ǹ���Ѱ·�Ƚ����⣬ֻ�и��� 8 �������ǿ��Ե���ģ������Ķ��ǲ�����ֱ�ӵ����
	//for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // Ѱ���� startId ����Ķ���
	//{
	//	pVert = m_vertsVec[neighborVertIdx];
	//	if (pVert->m_state != State::Closed && pVert->m_distance < minDist)
	//	{
	//		minDist = pVert->m_distance; // w������ startId �������
	//		minIdx = neighborVertIdx;
	//		bFindNextClosedVert = true;				// ˵�����ҵ���
	//	}
	//}

	// ֻҪ������Χ 8 ������Ϳ����ˣ���Ϊ����Ѱ·ֻ���Ǻ��Լ���Χ�� 8 �����Ӳ���Ȩ�أ��������ĸ�����û��Ȩ�ص�
	for (closedIdx = 0; closedIdx < closedVec.size(); ++closedIdx)
	{
		if (!m_vertsVec[closedVec[closedIdx]]->m_bNeighborValid)		// ����ھ���������Ч��
		{
			findNeighborVertIdArr(closedVec[closedIdx]);
			m_vertsVec[closedVec[closedIdx]]->setNeighborVertsId(m_neighborVertIdArr);
		}

		for (neighborVertIdx = 0; neighborVertIdx < m_vertsVec[closedVec[closedIdx]]->m_vertsIdVec.size(); ++neighborVertIdx)
		{
			pVert = m_vertsVec[m_vertsVec[closedVec[closedIdx]]->m_vertsIdVec[neighborVertIdx]];
			if (pVert->m_state != State::Closed && pVert->m_distance < minDist)
			{
				minDist = pVert->m_distance; // w������ startId �������
				minIdx = pVert->m_id;
				bFindNextClosedVert = true;				// ˵�����ҵ���
			}
		}
	}

	return bFindNextClosedVert;
}

void MGraph::modifyVertsDist(float& minDist, int& minIdx)
{
	int neighborVertIdx = 0;
	Vertex* pVert = nullptr;

	// �������ж��㣬��Ϊͨ�����㷨��Ȩ�ش洢�ھ����еģ����������ֱ�Ӵ洢�ھӶ��㣬�Ϳ���ֻ�����ھӶ���
	//for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // ������ǰ���·������
	//{
	//	pVert = m_vertsVec[neighborVertIdx];
		// �������V�����·������������·���ĳ��ȶ̵Ļ�
	//	if (pVert->m_state != State::Closed && (minDist + adjacentCost(minIdx, neighborVertIdx) < pVert->m_distance))
	//	{
			// ˵���ҵ�����̵�·�����޸�D[w] �� p[w]
	//		pVert->m_distance = minDist + adjacentCost(minIdx, neighborVertIdx); // �޸ĵ�ǰ·������
	//		pVert->m_nearestVert = m_vertsVec[minIdx];
	//	}
	//}

	// ֻ��Ҫ�������¼��� closed �Ķ�����ھӶ���
	if (!m_vertsVec[minIdx]->m_bNeighborValid)		// ����ھ���������Ч��
	{
		findNeighborVertIdArr(minIdx);
		m_vertsVec[minIdx]->setNeighborVertsId(m_neighborVertIdArr);
	}
	for (neighborVertIdx = 0; neighborVertIdx < m_vertsVec[minIdx]->m_vertsIdVec.size(); ++neighborVertIdx) // ������ǰ���·������
	{
		pVert = m_vertsVec[m_vertsVec[minIdx]->m_vertsIdVec[neighborVertIdx]];
		// �������V�����·������������·���ĳ��ȶ̵Ļ�
		if (pVert->m_state != State::Closed && (minDist + adjacentCost(minIdx, pVert->m_id) < pVert->m_distance))
		{
			// ˵���ҵ�����̵�·�����޸�D[w] �� p[w]
			pVert->m_distance = minDist + adjacentCost(minIdx, pVert->m_id); // �޸ĵ�ǰ·������
			pVert->m_nearestVert = m_vertsVec[minIdx];
		}
	}
}

void MGraph::createShortestPath(int startId, int endId)
{
	m_pathList.clear();
	m_closedVec.clear();

	initVerts(startId, endId);

	int openVertIdx = 0;		// ��δȷ�����ӵ������еĶ������������
	int neighborVertIdx = 0;
	int minIdx = 0;
	float minDist = 0;
	Vertex* pVert = nullptr;
	bool bFindShortestPath = false;

	resetAllVerts(startId);

	m_closedVec.push_back(startId);

	// �ܹ��� nVerts �����㣬�� startId ���Ѿ�ȷ�ϣ�ֻ��Ҫȷ��ʣ�µ� nVerts - 1 �Ϳ�����
	for (openVertIdx = 1; openVertIdx < m_vertsCount; ++openVertIdx)
	{
		// Ҫ���� m_closedVec �еĵ㣬����ֻ���� minIdx �����ĵ㣬������Щ·����ʼȨ�رȽ�С������Ȩ�رȽϴ󣬵�����Щ·����ʼȨ�رȽϴ󣬺���Ȩ�رȽ�С
		if (findNextClosedVert(minDist, minIdx, m_closedVec))	// ������ҵ�����һ����̵�δȷ�ϵ�����
		{
			// ע����ʼ����͵ڶ�������֮����û�� m_nearestVert �������Ҫ�ֹ�����һ������ŵ�·���б���ȥ
			pVert = m_vertsVec[minIdx];
			pVert->m_state = State::Closed; // ��Ŀǰ�ҵ�������Ķ�����Ϊ State::Closed 
			m_closedVec.push_back(minIdx);

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
		buildPath(m_endVert);
	}
}

std::list<Vertex*>& MGraph::getOrCreateShortestPath(int startId, int endId)
{
	if (!m_pathList.size())
	{
		createShortestPath(startId, endId);
	}

	return m_pathList;
}