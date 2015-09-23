#ifndef __PATHCACHE_H_
#define __PATHCACHE_H_

#include <vector>
#include <map>

class CacheItem
{
public:
	std::vector<int> m_vertsIdVec;			// ����·���б�
	bool m_bValid;
};

/**
 * @brief ·������
 */
class PathCache
{
protected:
	std::map<int, std::map<int, CacheItem*> > m_rowCol2PathMap;

public:
	PathCache();
	~PathCache();

	/**
	 * @brief ��ȡ
	 */
	CacheItem* getAndAddPathCache(int startId, int endId);
	CacheItem* getPathCache(int startId, int endId);
	bool isPathValid(int startId, int endId);
};

#endif