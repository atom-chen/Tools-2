#ifndef __MGRAPH_H_
#define __MGRAPH_H_

#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <list>

// 阻挡点
struct StopPoint
{

};

// 当前顶点的状态
enum class State 
{
	Closed,			// 如果已经确认了顶点，就是这个状态
	Open,			// 如果已经遍历，但是还没有确认就是这个状态
	Unknown			// 最初的状态就是这个状态
};

// 顶点数据
struct Vertex
{
	unsigned int m_id;
	State m_state;
	Vertex* m_nearestVert;
	float m_distance;

	void reset();
};

// 图
class MGraph 
{
public:
	typedef std::vector<Vertex*> VertVector;
	typedef std::map<int, StopPoint*> StopPtMap;

private:
	VertVector m_verts;			// 所有的定点
	int m_vertsCount;			// 定点总共数量
	int m_xCount;				// X 顶点数量
	int m_yCount;				// Y 顶点数量

	StopPtMap m_id2StopPtMap;

	// Dijkstra 算法需要的数据
	Vertex *m_startVert, *m_endVert;

protected:
	bool isHorizontalOrVerticalNeighbor(int vertId, int neighborVertId);		// 判断是它们之间的关系是水平还是垂直关系
	bool isHorizontalNeighbor(int vertId, int neighborVertId);
	bool isVerticalNeighbor(int vertId, int neighborVertId);
	bool isSlashNeighbor(int vertId, int neighborVertId);
	bool isBackSlashStopPoint(int vertId, int neighborVertId);
	/**
	 * @brief 两个顶点之间是否是邻居节点，就是两个节点之间相差为 1，只要在如下正方形的四个角，就算是邻居
	 * a	b
	 * c	d
	 */
	bool isNeighbor(int vertId, int neighborVertId);

public:
	MGraph();
	~MGraph();

	Vertex* getVertexById(int vertId);
	const VertVector& getVerts() const;

	Vertex* getVert(int id);
	size_t getVertsCount();
	void init(int xCount, int yCount);
	// 转换顶点的 Id 到顶点索引
	void convIdToXY(int vertId, int* x, int* y);
	int convXYToVertId(int x, int y);
	// 是否在阻挡点内
	bool isInStopPt(int nx, int ny);
	/**
	 * @brief 邻居格子成本
	 * @param vertId 起始顶点 Id
	 * @Param neighborVertId 邻居顶点 Id
	 *	5	6	7
	 *	4		0
	 *	3	2	1
	 */
	float adjacentCost(int vertId, int neighborVertId);
	/**
	 * @brief 添加一个阻挡点
	 */
	void addStopPoint(int nx, int ny, StopPoint* pStopPoint);

	// Dijkstra 算法需要的数据
	std::list<Vertex*> getShortestPath(unsigned int startId, unsigned int endId);
	std::list<Vertex*> buildPath(Vertex *endVert);

	void initializeNodes(unsigned int startId, unsigned int endId);
	bool checkFail(Vertex *endVert);			// 检查是否失败
};

#endif