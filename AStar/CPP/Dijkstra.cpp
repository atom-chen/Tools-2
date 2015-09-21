#include "Dijkstra.h"

#include <numeric>
#include <stdexcept>

Dijkstra::Dijkstra(Graph &graph) : m_graph(graph) 
{

}

Dijkstra::~Dijkstra() 
{

}

void Dijkstra::initialize_nodes(unsigned int start_id, unsigned int end_id) 
{
	m_start_node = m_end_node = nullptr;

	for (auto node : m_graph.get_nodes()) 
	{
		node->m_state = Node::State::Unknown;

		if (node->m_index == start_id) {
			m_start_node = node;
		}

		if (node->m_index == end_id) {
			m_end_node = node;
		}
	}

	if (m_start_node == nullptr || m_end_node == nullptr) {
		throw std::runtime_error("Failed to find the start/end node(s)!");
	}
}

std::list<Vertex*> Dijkstra::get_shortest_path(unsigned int start_id, unsigned int end_id)
{
	initialize_nodes(start_id, end_id);

	NodeHeap heap;
	heap.push(m_start_node);

	while (!heap.empty()) {
		Node *node = heap.pop();
		node->state = Node::State::Closed;

		if (node == m_end_node) {
			break;
		}

		for (auto &e : node->edges) {
			if (e.node->state != Node::State::Closed) {
				process_node(node, e.node, e.weight, heap);
			}
		}
	}

	return build_path(m_end_node);
}

void Dijkstra::ShortestPath_Dijkstra(int v0, int ve, int* final, int*p, int *D)
{
    int v, w, k, min;
    // 初始化数据
	unsigned int nVer = m_graph.getVertNum();
    for (v = 0; v < nVer; ++v)
    {
        final[v] = 0;    // 全部顶点初始化为未知对短路径状态
        D[v] = m_graph.getDist(v0, v); //将与V0点有连线的顶点加上权值
        p[v] = 0;    // 初始化路径数组p为0
    }
    D[v0] = 0;    // V0至V0路径为0
    final[v0] = 1;    // final[W]=1表示V0至V0不需要求路径

    // 开始主循环，每次求得V0到某个V顶点的最短路径
    for (v = 1; v < nVer; ++v)
    {
        min = std::numeric_limits<unsigned int>::max();    // 当前所知离V0顶点最近距离
        for (w = 0; w < nVer; ++w) // 寻找离V0最近的顶点
        {
            if (!final[w] && D[w] < min)
            {
                min = D[w]; // w顶点离V0顶点更近
                k = w;
            }
        }

        final[k] = 1; // 将目前找到的最近的顶点置为1

		if (k == ve)
		{
			break;
		}

        for (w = 0; w < nVer; ++w) // 修正当前最短路径距离
        {
            // 如果经过V顶点的路径比现在这条路径的长度短的话
            if (!final[w] && (min + m_graph.getDist(k, w) < D[w]))
            {
                // 说明找到了最短的路径，修改D[w] 和 p[w]
                D[w] = min + m_graph.getDist(k, w); // 修改当前路径长度
                p[w] = k;
            }
        }
    }
}