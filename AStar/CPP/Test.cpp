#include "MGraph.h"
#include <iostream>

void main()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);
	StopPoint* pStopPoint = nullptr;
	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);
	std::list<Vertex*> vertList;
	vertList = pMGraph->getShortestPath(0, 4);

	for (auto pVert : vertList)
	{
		std::cout << pVert->m_id << std::endl;
	}
}