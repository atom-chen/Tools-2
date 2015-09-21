#ifndef __DIJKSTRA_H_
#define __DIJKSTRA_H_

#include "Graph.h"

#include <list>

class Dijkstra 
{
public:
	Dijkstra(Graph &graph);
	~Dijkstra();

	Dijkstra& operator=(const Dijkstra&) = delete;

	std::list<Vertex*> get_shortest_path(unsigned int start_id, unsigned int end_id);
	void ShortestPath_Dijkstra(int v0, int ve, int* final, int*p, int *D);

private:
	void initialize_nodes(unsigned int start_id, unsigned int end_id);

	Graph &m_graph;
	Vertex *m_start_node, *m_end_node;

	int* m_final;
	int* m_preVert;
	int* m_dist;
};

#endif