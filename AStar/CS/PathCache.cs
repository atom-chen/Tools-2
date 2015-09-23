using System.Collections.Generic;

namespace SDK.Lib
{
    class CacheItem
    {
        public List<int> m_vertsIdVec = null;          // ����·���б�
        public bool m_bValid;

        public CacheItem()
        {
            m_vertsIdVec = new List<int>();
        }
    };

    class PathCache
    {
        Dictionary<int, Dictionary<int, CacheItem>> m_rowCol2PathMap;

        public PathCache()
        {
            m_rowCol2PathMap = new Dictionary<int, Dictionary<int, CacheItem>>();
        }

        public void dispose()
        {
            foreach (var colMap in m_rowCol2PathMap)
            {
                foreach (var cacheItem in colMap.Value)
                {

                }
            }
        }

        public CacheItem getAndAddPathCache(int startId, int endId)
        {
            if(!m_rowCol2PathMap.ContainsKey(startId))
            {
                m_rowCol2PathMap[startId] = new Dictionary<int, CacheItem>();
            }
            if(!m_rowCol2PathMap[startId].ContainsKey(endId))
            {
                m_rowCol2PathMap[startId][endId] = new CacheItem();
            }

            m_rowCol2PathMap[startId][endId].m_vertsIdVec.Clear();
            m_rowCol2PathMap[startId][endId].m_bValid = true;
            return m_rowCol2PathMap[startId][endId];
        }

        public CacheItem getPathCache(int startId, int endId)
        {
            if(m_rowCol2PathMap.ContainsKey(startId))
            {
                if(m_rowCol2PathMap[startId].ContainsKey(endId))
                {
                    return m_rowCol2PathMap[startId][endId];
                }
            }
            return null;
        }

        public bool isPathValid(int startId, int endId)
        {
            if (m_rowCol2PathMap.ContainsKey(startId))
            {
                if (m_rowCol2PathMap[startId].ContainsKey(endId))
                {
                    if(m_rowCol2PathMap[startId][endId].m_bValid)
                    {
                        return true;
                    }
                }
            }

            return false;
        }
    }
}