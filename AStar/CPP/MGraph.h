#ifndef __MGRAPH_H_
#define __MGRAPH_H_

#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <list>
#include <vector>
#include "PathCache.h"

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
	bool m_bNeighborValid;		// 邻居数据是否有效，因为可能动态修改阻挡点
	std::vector<int> m_vertsIdVec;			// 保存邻居顶点 Id，这个数值只有在使用的时候才会动态生成，初始化的时候并不生成

	void reset();
	void setNeighborVertsId(int* neighborVertIdArr, int len = 8);
};

// 图
class MGraph 
{
public:
	typedef std::vector<Vertex*> VertVector;
	typedef std::map<int, StopPoint*> StopPtMap;

private:
	VertVector m_vertsVec;			// 所有的顶点，启动的时候，所有的顶点全部创建，不是需要的时候再创建，如果需要的时候再创建，就需要各种判断
	int m_vertsCount;			// 定点总共数量
	int m_xCount;				// X 顶点数量
	int m_yCount;				// Y 顶点数量

	StopPtMap m_id2StopPtMap;

	// Dijkstra 算法需要的数据
	Vertex *m_startVert, *m_endVert;

	// 最终路径列表
	std::list<Vertex*> m_pathList;	// 使用 List ，主要是使用 push_front 这个接口
	// 计算中需要用的 8 个邻居顶点索引
	int m_neighborVertIdArr[8];
	std::vector<int> m_closedVec;	// 已经确认的队列列表

	// 路径缓存列表
	PathCache m_pathCache;

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
	/**
	 * @brief重置所有的顶点数据
	 */
	void resetAllVerts(unsigned int startId);
	/**
	 * @brief 查找下一个确认的顶点
	 */
	bool findNextClosedVert(float& minDist, int& minIdx, std::vector<int>& closedVec);
	/**
	 * @brief 修改最短路径
	 */
	void modifyVertsDist(float& minDist, int& minIdx);
	/**
	 * @brief 查找顶点邻居 Id 数组
	 */
	void findNeighborVertIdArr(int vertId);
	/**
	 * @brief 根据顶点 Id 获取对应的顶点的数据
	 */
	void initVerts(unsigned int startId, unsigned int endId);
	//bool checkFail(Vertex *endVert);			// 检查是否失败
	void buildPath(Vertex *endVert);
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
	* @brief 转换顶点 Id 向量到顶点 List
	*/
	void convVertIdVec2VertList(std::vector<int>& vertsIdVec);
	void convVertList2VertIdVec(std::vector<int>& vertsIdVec);

	/**
	 * @breif 设置与 vertId 为邻居节点的其它顶点的邻居数据无效
	 */
	void setNeighborInvalidByVertId(int vertId);

public:
	MGraph();
	~MGraph();

	Vertex* getVertexById(int vertId);
	const VertVector& getVertsVec() const;
	size_t getVertsCount();
	void init(int xCount, int yCount);
	// 转换顶点的 Id 到顶点索引
	void convVertIdToXY(int vertId, int& x, int& y);
	int convXYToVertId(int x, int y);
	// 是否在阻挡点内
	bool isInStopPt(int nx, int ny);
	/**
	 * @brief 添加一个阻挡点
	 */
	void addStopPoint(int nx, int ny, StopPoint* pStopPoint);

	// Dijkstra 算法需要的数据
	/**
	* @brief 获取最短路径
	*/
	std::list<Vertex*>& getShortestPath();
	void createShortestPath(int startId, int endId);
	std::list<Vertex*>& getOrCreateShortestPath(int startId, int endId);

	bool isPathCacheValid(int startId, int endId);
	std::list<Vertex*>& getShortestPathFromPathCache(int startId, int endId);
	void clearPath();				// 清理当前的路径
	void clearAllStopPoint();		// 清理所有的阻挡点
};

#endif