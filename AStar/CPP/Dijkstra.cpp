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
    // ��ʼ������
	unsigned int nVer = m_graph.getVertNum();
    for (v = 0; v < nVer; ++v)
    {
        final[v] = 0;    // ȫ�������ʼ��Ϊδ֪�Զ�·��״̬
        D[v] = m_graph.getDist(v0, v); //����V0�������ߵĶ������Ȩֵ
        p[v] = 0;    // ��ʼ��·������pΪ0
    }
    D[v0] = 0;    // V0��V0·��Ϊ0
    final[v0] = 1;    // final[W]=1��ʾV0��V0����Ҫ��·��

    // ��ʼ��ѭ����ÿ�����V0��ĳ��V��������·��
    for (v = 1; v < nVer; ++v)
    {
        min = std::numeric_limits<unsigned int>::max();    // ��ǰ��֪��V0�����������
        for (w = 0; w < nVer; ++w) // Ѱ����V0����Ķ���
        {
            if (!final[w] && D[w] < min)
            {
                min = D[w]; // w������V0�������
                k = w;
            }
        }

        final[k] = 1; // ��Ŀǰ�ҵ�������Ķ�����Ϊ1

		if (k == ve)
		{
			break;
		}

        for (w = 0; w < nVer; ++w) // ������ǰ���·������
        {
            // �������V�����·������������·���ĳ��ȶ̵Ļ�
            if (!final[w] && (min + m_graph.getDist(k, w) < D[w]))
            {
                // ˵���ҵ�����̵�·�����޸�D[w] �� p[w]
                D[w] = min + m_graph.getDist(k, w); // �޸ĵ�ǰ·������
                p[w] = k;
            }
        }
    }
}