#include "Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{
	for (auto p : m_nodes)
	{
		delete p;
	}
}