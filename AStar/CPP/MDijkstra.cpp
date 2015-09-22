#include "MGraph.h"

#include <numeric>
#include <stdexcept>
#include <list>

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

std::list<Vertex*> MGraph::buildPath(Vertex *endVert)
{
	std::list<Vertex*> pathList;

	Vertex *vert = endVert;
	while (vert != nullptr) 
	{
		pathList.push_front(vert);
		vert = vert->m_nearestVert;
	}
	pathList.push_front(m_startVert);		// 把最初的顶点放进去
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

std::list<Vertex*> MGraph::getShortestPath(unsigned int startId, unsigned int endId)
{
	initializeNodes(startId, endId);

	int v, w, k;
	float min;
	int nVer = m_vertsCount;
	Vertex* pVert = nullptr;

	// 初始化数据
	for (v = 0; v < nVer; ++v)
	{
		m_startVert->m_state = State::Unknown;    // 全部顶点初始化为未知对短路径状态
		pVert = m_verts[v];
		pVert->m_distance = adjacentCost(startId, v); //将与V0点有连线的顶点加上权值
		pVert->m_nearestVert = nullptr;    // 初始化路径数组p为0
	}

	m_startVert->m_distance = 0;    // V0至V0路径为0
	m_startVert->m_state = State::Closed;    // final[W]=1表示V0至V0不需要求路径

	// 开始主循环，每次求得V0到某个V顶点的最短路径
	for (v = 1; v < nVer; ++v)
	{
		min = std::numeric_limits<float>::max();    // 当前所知离V0顶点最近距离
		for (w = 0; w < nVer; ++w) // 寻找离V0最近的顶点
		{
			pVert = m_verts[w];
			if (pVert->m_state != State::Closed && pVert->m_distance < min)
			{
				min = pVert->m_distance; // w顶点离V0顶点更近
				k = w;
			}
		}

		// 注意起始顶点和第二个顶点之间是没有 m_nearestVert ，因此需要手工将第一个顶点放到路径列表中去
		pVert = m_verts[k];
		pVert->m_state = State::Closed; // 将目前找到的最近的顶点置为1

		for (w = 0; w < nVer; ++w) // 修正当前最短路径距离
		{
			pVert = m_verts[w];
			// 如果经过V顶点的路径比现在这条路径的长度短的话
			if (pVert->m_state != State::Closed && (min + adjacentCost(k, w) < pVert->m_distance))
			{
				// 说明找到了最短的路径，修改D[w] 和 p[w]
				pVert->m_distance = min + adjacentCost(k, w); // 修改当前路径长度
				pVert->m_nearestVert = m_verts[k];
			}
		}

		if (k == endId)			// 如果查找到
		{
			break;
		}
	}

	return buildPath(m_endVert);
}