#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <vector>

struct Vertex
{
	enum class State 
	{
		Closed, Open, Unknown
	};

	State m_state;
};

class Graph 
{
public:
	typedef std::vector<Vertex*> VertexVec;

	Graph();
	~Graph();

	inline const VertexVec& get_Vertexs() const
	{
		return m_nodes;
	}

	inline Vertex* get_or_add(int index)
	{
		Vertex *node = m_nodes[index];
		if (node == nullptr) 
		{
			node = new Vertex();

			m_nodes[index] = node;
		}

		return node;
	}

	inline unsigned int getVertNum()
	{
		return m_nVert;
	}

	inline unsigned int getDist(unsigned int from, unsigned int to)
	{
		return 0;
	}

private:
	VertexVec m_nodes;
	unsigned int m_nVert;		// ¶¥µãÊý
};

#endif