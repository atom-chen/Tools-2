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
	if (!endVert->m_nearestVert)	// 如果终点没有前面指向的节点
	{
		if (!isNeighbor(m_startVert->m_id, m_endVert->m_id))		// 如果不是邻居，必然失败
		{
			return true;
		}
		else if (isSlashNeighbor(m_startVert->m_id, m_endVert->m_id))		// 如果是对角邻居
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
	m_pathList.push_front(m_startVert);		// 把最初的顶点放进去

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

		if (m_startVert != nullptr && m_endVert != nullptr)			// 如果查找到就退出
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
	// 初始化数据
	for (int vertIdx = 0; vertIdx < m_vertsCount; ++vertIdx)
	{
		m_startVert->m_state = State::Unknown;    // 全部顶点初始化为未知对短路径状态
		pVert = m_verts[vertIdx];
		pVert->m_distance = adjacentCost(startId, vertIdx); //将与 startId 点有连线的顶点加上权值
		pVert->m_nearestVert = nullptr;    // 初始化路径的前一个顶点
	}

	m_startVert->m_distance = 0;    //  startId 至 startId 路径为0
	m_startVert->m_state = State::Closed;    // m_startVert->m_state 表示 startId 至 startId 不需要求路径，已经添加到确认队列中了
}

bool MGraph::findNextClosedVert(float& minDist, int& minIdx)
{
	Vertex* pVert = nullptr;
	int neighborVertIdx = 0;
	minDist = std::numeric_limits<float>::max();    // 当前所知离 startId 顶点最近距离
	bool bFindNextClosedVert = false;
	for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // 寻找离 startId 最近的顶点
	{
		pVert = m_verts[neighborVertIdx];
		if (pVert->m_state != State::Closed && pVert->m_distance < minDist)
		{
			minDist = pVert->m_distance; // w顶点离 startId 顶点更近
			minIdx = neighborVertIdx;
			bFindNextClosedVert = true;				// 说明查找到了
		}
	}

	return bFindNextClosedVert;
}

void MGraph::modifyVertsDist(float& minDist, int& minIdx)
{
	int neighborVertIdx = 0;
	Vertex* pVert = nullptr;

	for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // 修正当前最短路径距离
	{
		pVert = m_verts[neighborVertIdx];
		// 如果经过V顶点的路径比现在这条路径的长度短的话
		if (pVert->m_state != State::Closed && (minDist + adjacentCost(minIdx, neighborVertIdx) < pVert->m_distance))
		{
			// 说明找到了最短的路径，修改D[w] 和 p[w]
			pVert->m_distance = minDist + adjacentCost(minIdx, neighborVertIdx); // 修改当前路径长度
			pVert->m_nearestVert = m_verts[minIdx];
		}
	}
}

std::list<Vertex*>& MGraph::getShortestPath(unsigned int startId, unsigned int endId)
{
	m_pathList.clear();

	initVerts(startId, endId);

	int openVertIdx = 0;		// 还未确定添加到队列中的顶点遍历的索引
	int neighborVertIdx = 0;
	int minIdx = 0;
	float minDist = 0;
	Vertex* pVert = nullptr;
	bool bFindShortestPath = false;

	resetAllVerts(startId);

	// 总共就 nVerts 个顶点，第 startId 个已经确认，只需要确认剩下的 nVerts - 1 就可以了
	for (openVertIdx = 1; openVertIdx < m_vertsCount; ++openVertIdx)
	{
		if (findNextClosedVert(minDist, minIdx))	// 如果查找到了下一个最短的未确认的索引
		{
			// 注意起始顶点和第二个顶点之间是没有 m_nearestVert ，因此需要手工将第一个顶点放到路径列表中去
			pVert = m_verts[minIdx];
			pVert->m_state = State::Closed; // 将目前找到的最近的顶点置为 State::Closed 

			modifyVertsDist(minDist, minIdx);
		}
		else				// 如果找不到下一个最小的顶点索引，就直接退出吧，没有最短距离
		{
			bFindShortestPath = false;
			break;
		}

		if (minIdx == endId)			// 如果查找到
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