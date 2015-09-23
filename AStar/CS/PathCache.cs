class CacheItem
{
    public std::vector<int> m_vertsIdVec;          // 顶点路径列表
    public bool m_bValid;
};

class PathCache
{
	std::map<int, std::map<int, CacheItem*>> m_rowCol2PathMap;

    public PathCache()
    {

    }

    public void dispose()
    {
        for (auto colMap : m_rowCol2PathMap)
        {
            for (auto cacheItem : colMap.second)
            {
                delete cacheItem.second;
            }
        }
    }

    CacheItem* getAndAddPathCache(int startId, int endId)
    {
        if (!m_rowCol2PathMap[startId][endId])
        {
            m_rowCol2PathMap[startId][endId] = new CacheItem();
        }

        m_rowCol2PathMap[startId][endId]->m_vertsIdVec.clear();
        m_rowCol2PathMap[startId][endId]->m_bValid = true;
        return m_rowCol2PathMap[startId][endId];
    }

    CacheItem* getPathCache(int startId, int endId)
    {
        return m_rowCol2PathMap[startId][endId];
    }

    bool isPathValid(int startId, int endId)
    {
        if (!m_rowCol2PathMap[startId][endId] || m_rowCol2PathMap[startId][endId]->m_bValid)
        {
            return false;
        }

        return true;
    }
}