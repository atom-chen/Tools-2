#include "MGraph.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <sstream>

// 测试 0 个阻挡点
std::list<Vertex*> test0Stop(MGraph* pMGraph)
{
	std::list<Vertex*> vertList;
	if (pMGraph->isPathCacheValid(0, 4))
	{
		vertList = pMGraph->getShortestPathFromPathCache(0, 4);
	}
	else
	{
		vertList = pMGraph->getOrCreateShortestPath(0, 4);
	}

	delete pMGraph;

	return vertList;
}

// 测试 1 个阻挡点
std::list<Vertex*> test1Stop(MGraph* pMGraph)
{
	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	std::list<Vertex*> vertList;
	if (pMGraph->isPathCacheValid(0, 8))
	{
		vertList = pMGraph->getShortestPathFromPathCache(0, 8);
	}
	else
	{
		vertList = pMGraph->getOrCreateShortestPath(0, 8);
	}

	return vertList;
}

// 测试 2 个阻挡点
std::list<Vertex*> test2Stop(MGraph* pMGraph)
{
	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 1, pStopPoint);

	std::list<Vertex*> vertList;
	if (pMGraph->isPathCacheValid(0, 8))
	{
		vertList = pMGraph->getShortestPathFromPathCache(0, 8);
	}
	else
	{
		vertList = pMGraph->getOrCreateShortestPath(0, 8);
	}

	return vertList;
}

// 测试 3 个阻挡点
std::list<Vertex*> test3Stop(MGraph* pMGraph)
{
	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 1, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 2, pStopPoint);

	std::list<Vertex*> vertList;
	if (pMGraph->isPathCacheValid(0, 8))
	{
		vertList = pMGraph->getShortestPathFromPathCache(0, 8);
	}
	else
	{
		vertList = pMGraph->getOrCreateShortestPath(0, 8);
	}

	return vertList;
}


// 测试对角线阻挡点
std::list<Vertex*> test4Stop(MGraph* pMGraph)
{
	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 0, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(0, 1, pStopPoint);

	std::list<Vertex*> vertList;
	if (pMGraph->isPathCacheValid(1, 1))
	{
		vertList = pMGraph->getShortestPathFromPathCache(1, 1);
	}
	else
	{
		vertList = pMGraph->getOrCreateShortestPath(1, 1);
	}

	return vertList;
}

// 测试最长阻挡点
std::list<Vertex*> test5Stop(MGraph* pMGraph)
{
	StopPoint* pStopPoint = nullptr;

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(1, 1, pStopPoint);

	pStopPoint = new StopPoint();
	pMGraph->addStopPoint(0, 1, pStopPoint);

	std::list<Vertex*> vertList;
	if (pMGraph->isPathCacheValid(0, 6))
	{
		vertList = pMGraph->getShortestPathFromPathCache(0, 6);
	}
	else
	{
		vertList = pMGraph->getOrCreateShortestPath(0, 6);
	}

	return vertList;
}

void serializePath(std::list<Vertex*>& vertList, std::stringstream& strStream)
{
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
		strStream << "can not find path" << "\n";
	}
}


void main()
{
	MGraph* pMGraph = new MGraph();
	pMGraph->init(3, 3, 1, 1);

	std::list<Vertex*> vertList;
	FILE* pFile = nullptr;
	pFile = fopen("E:\\aaa.txt", "w");
	std::stringstream strStream;

	vertList = test5Stop(pMGraph);
	serializePath(vertList, strStream);
	pMGraph->clearAllStopPoint();
	pMGraph->clearPath();

	vertList = test4Stop(pMGraph);
	serializePath(vertList, strStream);
	pMGraph->clearAllStopPoint();
	pMGraph->clearPath();

	vertList = test2Stop(pMGraph);
	serializePath(vertList, strStream);
	pMGraph->clearAllStopPoint();
	pMGraph->clearPath();

	vertList = test2Stop(pMGraph);
	serializePath(vertList, strStream);
	pMGraph->clearAllStopPoint();
	pMGraph->clearPath();

	fwrite(strStream.str().c_str(), strStream.str().length(), 1, pFile);
	fclose(pFile);
	delete pMGraph;
	//system("pause");
}
