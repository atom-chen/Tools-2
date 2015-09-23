#include "PathCache.h"

PathCache::PathCache()
{

}

PathCache::~PathCache()
{
	for (auto colMap : m_rowCol2PathMap)
	{
		for (auto cacheItem : colMap.second)
		{
			delete cacheItem.second;
		}
	}
}

CacheItem* PathCache::getAndAddPathCache(int startId, int endId)
{
	if (!m_rowCol2PathMap[startId][endId])
	{
		m_rowCol2PathMap[startId][endId] = new CacheItem();
	}

	m_rowCol2PathMap[startId][endId]->m_vertsIdVec.clear();
	m_rowCol2PathMap[startId][endId]->m_bValid = true;
	return m_rowCol2PathMap[startId][endId];
}

CacheItem* PathCache::getPathCache(int startId, int endId)
{
	return m_rowCol2PathMap[startId][endId];
}

bool PathCache::isPathValid(int startId, int endId)
{
	if (m_rowCol2PathMap[startId][endId] && m_rowCol2PathMap[startId][endId]->m_bValid)
	{
		return false;
	}

	return false;
}