public partial class MGraph
{
    void buildPath(Vertex *endVert)
    {
	    Vertex *vert = endVert;
	    while (vert != nullptr)
	    {
		    m_pathList.push_front(vert);
		    vert = vert->m_nearestVert;
	    }
	    m_pathList.push_front(m_startVert);		// 把最初的顶点放进去

	    //return m_pathList;
    }

    void initVerts(unsigned int startId, unsigned int endId)
    {
	    m_startVert = nullptr;
	    m_endVert = nullptr;

	    int nx = 0;
	    int ny = 0;

	    convVertIdToXY(startId, nx, ny);
	    if (nx >= 0 && nx < m_xCount
		    && ny >= 0 && ny < m_yCount)
	    {
		    m_startVert = m_vertsVec[startId];
	    }

	    convVertIdToXY(endId, nx, ny);
	    if (nx >= 0 && nx < m_xCount
		    && ny >= 0 && ny < m_yCount)
	    {
		    m_endVert = m_vertsVec[endId];
	    }

	    if (m_startVert == nullptr || m_endVert == nullptr) 
	    {
		    throw std::runtime_error("Failed to find the start/end node(s)!");
	    }


	    m_startVert->m_distance = 0;
    }

    void resetAllVerts(unsigned int startId)
    {
	    Vertex* pVert = nullptr;
	    // 初始化数据
	    for (int vertIdx = 0; vertIdx < m_vertsCount; ++vertIdx)
	    {
		    pVert = m_vertsVec[vertIdx];
		    pVert->m_state = State::Unknown;    // 全部顶点初始化为未知对短路径状态
		    pVert->m_distance = adjacentCost(startId, vertIdx); //将与 startId 点有连线的顶点加上权值
		    pVert->m_nearestVert = nullptr;    // 初始化路径的前一个顶点
	    }

	    m_startVert->m_distance = 0;    //  startId 至 startId 路径为0
	    m_startVert->m_state = State::Closed;    // m_startVert->m_state 表示 startId 至 startId 不需要求路径，已经添加到确认队列中了
    }

    bool findNextClosedVert(float& minDist, int& minIdx, std::vector<int>& closedVec)
    {
	    Vertex* pVert = nullptr;
	    int closedIdx = 0;
	    int neighborVertIdx = 0;
	    minDist = std::numeric_limits<float>::max();    // 当前所知离 startId 顶点最近距离
	    bool bFindNextClosedVert = false;
	    // 遍历所有顶点，查找最近路径，但是格子寻路比较特殊，只有附近 8 个顶点是可以到达的，其它的都是不可以直接到达的
	    //for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // 寻找离 startId 最近的顶点
	    //{
	    //	pVert = m_vertsVec[neighborVertIdx];
	    //	if (pVert->m_state != State::Closed && pVert->m_distance < minDist)
	    //	{
	    //		minDist = pVert->m_distance; // w顶点离 startId 顶点更近
	    //		minIdx = neighborVertIdx;
	    //		bFindNextClosedVert = true;				// 说明查找到了
	    //	}
	    //}

	    // 只要遍历周围 8 个顶点就可以了，因为格子寻路只能是和自己周围的 8 个格子才有权重，和其它的格子是没有权重的
	    for (closedIdx = 0; closedIdx < closedVec.size(); ++closedIdx)
	    {
		    if (!m_vertsVec[closedVec[closedIdx]]->m_bNeighborValid)		// 如果邻居数据是无效的
		    {
			    findNeighborVertIdArr(closedVec[closedIdx]);
			    m_vertsVec[closedVec[closedIdx]]->setNeighborVertsId(m_neighborVertIdArr);
		    }

		    for (neighborVertIdx = 0; neighborVertIdx < m_vertsVec[closedVec[closedIdx]]->m_vertsIdVec.size(); ++neighborVertIdx)
		    {
			    pVert = m_vertsVec[m_vertsVec[closedVec[closedIdx]]->m_vertsIdVec[neighborVertIdx]];
			    if (pVert->m_state != State::Closed && pVert->m_distance < minDist)
			    {
				    minDist = pVert->m_distance; // w顶点离 startId 顶点更近
				    minIdx = pVert->m_id;
				    bFindNextClosedVert = true;				// 说明查找到了
			    }
		    }
	    }

	    return bFindNextClosedVert;
    }

    void modifyVertsDist(float& minDist, int& minIdx)
    {
	    int neighborVertIdx = 0;
	    Vertex* pVert = nullptr;

	    // 遍历所有顶点，因为通常的算法是权重存储在矩阵中的，如果顶点中直接存储邻居顶点，就可以只遍历邻居顶点
	    //for (neighborVertIdx = 0; neighborVertIdx < m_vertsCount; ++neighborVertIdx) // 修正当前最短路径距离
	    //{
	    //	pVert = m_vertsVec[neighborVertIdx];
		    // 如果经过V顶点的路径比现在这条路径的长度短的话
	    //	if (pVert->m_state != State::Closed && (minDist + adjacentCost(minIdx, neighborVertIdx) < pVert->m_distance))
	    //	{
			    // 说明找到了最短的路径，修改D[w] 和 p[w]
	    //		pVert->m_distance = minDist + adjacentCost(minIdx, neighborVertIdx); // 修改当前路径长度
	    //		pVert->m_nearestVert = m_vertsVec[minIdx];
	    //	}
	    //}

	    // 只需要遍历最新加入 closed 的顶点的邻居顶点
	    if (!m_vertsVec[minIdx]->m_bNeighborValid)		// 如果邻居数据是无效的
	    {
		    findNeighborVertIdArr(minIdx);
		    m_vertsVec[minIdx]->setNeighborVertsId(m_neighborVertIdArr);
	    }
	    for (neighborVertIdx = 0; neighborVertIdx < m_vertsVec[minIdx]->m_vertsIdVec.size(); ++neighborVertIdx) // 修正当前最短路径距离
	    {
		    pVert = m_vertsVec[m_vertsVec[minIdx]->m_vertsIdVec[neighborVertIdx]];
		    // 如果经过V顶点的路径比现在这条路径的长度短的话
		    if (pVert->m_state != State::Closed && (minDist + adjacentCost(minIdx, pVert->m_id) < pVert->m_distance))
		    {
			    // 说明找到了最短的路径，修改D[w] 和 p[w]
			    pVert->m_distance = minDist + adjacentCost(minIdx, pVert->m_id); // 修改当前路径长度
			    pVert->m_nearestVert = m_vertsVec[minIdx];
		    }
	    }
    }

    std::list<Vertex*>& getShortestPath()
    {
	    return m_pathList;
    }

    void createShortestPath(int startId, int endId)
    {
	    m_pathList.clear();
	    m_closedVec.clear();

	    initVerts(startId, endId);

	    int openVertIdx = 0;		// 还未确定添加到队列中的顶点遍历的索引
	    int neighborVertIdx = 0;
	    int minIdx = 0;
	    float minDist = 0;
	    Vertex* pVert = nullptr;
	    bool bFindShortestPath = false;

	    resetAllVerts(startId);

	    m_closedVec.push_back(startId);

	    // 总共就 nVerts 个顶点，第 startId 个已经确认，只需要确认剩下的 nVerts - 1 就可以了
	    for (openVertIdx = 1; openVertIdx < m_vertsCount; ++openVertIdx)
	    {
		    // 要遍历 m_closedVec 中的点，不能只遍历 minIdx 附近的点，可能有些路径开始权重比较小，后面权重比较大，但是有些路径开始权重比较大，后期权重比较小
		    if (findNextClosedVert(minDist, minIdx, m_closedVec))	// 如果查找到了下一个最短的未确认的索引
		    {
			    // 注意起始顶点和第二个顶点之间是没有 m_nearestVert ，因此需要手工将第一个顶点放到路径列表中去
			    pVert = m_vertsVec[minIdx];
			    pVert->m_state = State::Closed; // 将目前找到的最近的顶点置为 State::Closed 
			    m_closedVec.push_back(minIdx);

			    modifyVertsDist(minDist, minIdx);
		    }
		    else				// 如果找不到下一个最小的顶点索引，就直接退出吧，没有最短距离
		    {
			    bFindShortestPath = false;
			    break;
		    }

		    if (minIdx == endId)			// 如果查找到
		    {
			    bFindShortestPath = true;
			    break;
		    }
	    }

	    if (bFindShortestPath)
	    {
		    buildPath(m_endVert);	// 生成路径列表
		    convVertList2VertIdVec(m_pathCache.getAndAddPathCache(startId, endId)->m_vertsIdVec);		// 缓存目录
	    }
    }

    std::list<Vertex*>& getOrCreateShortestPath(int startId, int endId)
    {
	    if (!m_pathList.size())
	    {
		    createShortestPath(startId, endId);
	    }

	    return m_pathList;
    }

    void convVertIdVec2VertList(std::vector<int>& vertsIdVec)
    {
	    m_pathList.clear();
	    for (auto vertId : vertsIdVec)
	    {
		    m_pathList.push_back(m_vertsVec[vertId]);
	    }
    }

    void convVertList2VertIdVec(std::vector<int>& vertsIdVec)
    {
	    for (auto vert : m_pathList)
	    {
		    vertsIdVec.push_back(vert->m_id);
	    }
    }

    bool isPathCacheValid(int startId, int endId)
    {
	    return m_pathCache.isPathValid(startId, endId);
    }

    std::list<Vertex*>& getShortestPathFromPathCache(int startId, int endId)
    {
	    if (isPathCacheValid(startId, endId))
	    {
		    convVertIdVec2VertList(m_pathCache.getPathCache(startId, endId)->m_vertsIdVec);
	    }
	    else
	    {
		    m_pathList.clear();
	    }

	    return m_pathList;
    }

    void clearPath()
    {
	    m_pathList.clear();
    }

    void clearAllStopPoint()
    {
	    for (auto vert : m_vertsVec)
	    {
		    if (vert->m_pStopPoint)		// 可能通过 m_id2StopPtMap[idx] 导致添加数据，因此这里判断
		    {
			    setNeighborInvalidByVertId(vert->m_id);
			    delete vert->m_pStopPoint;
			    vert->m_pStopPoint = nullptr;
		    }
	    }
    }
}