#include "MGraph.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <sstream>

// 测试 0 个阻挡点
std::list<Vertex*> test0Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getOrCreateShortestPath(0, 4);

	return vertList;
}

// 测试 1 个阻挡点
std::list<Vertex*> test1Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getOrCreateShortestPath(0, 8);

	return vertList;
}

// 测试 2 个阻挡点
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
	vertList = pMGraph->getOrCreateShortestPath(0, 8);

	return vertList;
}

// 测试 3 个阻挡点
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
	vertList = pMGraph->getOrCreateShortestPath(0, 8);

	return vertList;
}


// 测试对角线阻挡点
std::list<Vertex*> test4Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(0, 1, pStopPoint);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getOrCreateShortestPath(1, 1);

	return vertList;
}

// 测试最长阻挡点
std::list<Vertex*> test5Stop()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3);

	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 1, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(0, 1, pStopPoint);

	std::list<Vertex*> vertList;
	vertList = pMGraph->getOrCreateShortestPath(0, 6);

	return vertList;
}


void main()
{
	std::list<Vertex*> vertList;
	vertList = test5Stop();
	FILE* pFile = nullptr;
	pFile = fopen("E:\\aaa.txt", "w");
	std::stringstream strStream;

	if (vertList.size() > 0)
	{
		for (auto pVert : vertList)
		{
			// std::cout << pVert->m_id << std::endl;
			strStream << "Vert ID = " << pVert->m_id << "\n";
		}
	}
	else
	{
		strStream << "can not find path";
	}

	fwrite(strStream.str().c_str(), strStream.str().length(), 1, pFile);
	fclose(pFile);
	system("pause");
}
