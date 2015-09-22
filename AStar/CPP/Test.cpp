#include "MGraph.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <sstream>

// ²âÊÔ 0 ¸ö×èµ²µã
std::list<Vertex*> test0Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getShortestPath(0, 4);

	return vertList;
}

// ²âÊÔ 1 ¸ö×èµ²µã
std::list<Vertex*> test1Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getShortestPath(0, 8);

	return vertList;
}

// ²âÊÔ 2 ¸ö×èµ²µã
std::list<Vertex*> test2Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 1, pStopPoint);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getShortestPath(0, 8);

	return vertList;
}

// ²âÊÔ 3 ¸ö×èµ²µã
std::list<Vertex*> test3Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 1, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 2, pStopPoint);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getShortestPath(0, 8);

	return vertList;
}

void main()
{
	std::list<Vertex*> vertList;
	vertList = test0Stop();
	FILE* pFile = nullptr;
	pFile = fopen("E:\\aaa.txt", "w");
	std::stringstream strStream;
	for (auto pVert : vertList)
	{
		// std::cout << pVert->m_id << std::endl;
		strStream << "Vert ID = " << pVert->m_id << "\n";
	}

	fwrite(strStream.str().c_str(), strStream.str().length(), 1, pFile);
	fclose(pFile);
	system("pause");
}
