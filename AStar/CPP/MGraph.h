#ifndef __MGRAPH_H_
#define __MGRAPH_H_

#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <list>
#include <vector>

// �赲��
struct StopPoint
{

};

// ��ǰ�����״̬
enum class State 
{
	Closed,			// ����Ѿ�ȷ���˶��㣬�������״̬
	Open,			// ����Ѿ����������ǻ�û��ȷ�Ͼ������״̬
	Unknown			// �����״̬�������״̬
};

// ��������
struct Vertex
{
	unsigned int m_id;
	State m_state;
	Vertex* m_nearestVert;
	float m_distance;
	bool m_bNeighborValid;		// �ھ������Ƿ���Ч����Ϊ���ܶ�̬�޸��赲��
	std::vector<int> m_vertsIdVec;			// �����ھӶ��� Id

	void reset();
	void setNeighborVertsId(int* neighborVertIdArr, int len = 8);
};

// ͼ
class MGraph 
{
public:
	typedef std::vector<Vertex*> VertVector;
	typedef std::map<int, StopPoint*> StopPtMap;

private:
	VertVector m_verts;			// ���еĶ���
	int m_vertsCount;			// �����ܹ�����
	int m_xCount;				// X ��������
	int m_yCount;				// Y ��������

	StopPtMap m_id2StopPtMap;

	// Dijkstra �㷨��Ҫ������
	Vertex *m_startVert, *m_endVert;

	// ����·���б�
	std::list<Vertex*> m_pathList;
	// ��������Ҫ�õ� 8 ���ھӶ�������
	int m_neighborVertIdArr[8];
	std::vector<int> m_closedVec;	// �Ѿ�ȷ�ϵĶ����б�

protected:
	bool isHorizontalOrVerticalNeighbor(int vertId, int neighborVertId);		// �ж�������֮��Ĺ�ϵ��ˮƽ���Ǵ�ֱ��ϵ
	bool isHorizontalNeighbor(int vertId, int neighborVertId);
	bool isVerticalNeighbor(int vertId, int neighborVertId);
	bool isSlashNeighbor(int vertId, int neighborVertId);
	bool isBackSlashStopPoint(int vertId, int neighborVertId);
	/**
	 * @brief ��������֮���Ƿ����ھӽڵ㣬���������ڵ�֮�����Ϊ 1��ֻҪ�����������ε��ĸ��ǣ��������ھ�
	 * a	b
	 * c	d
	 */
	bool isNeighbor(int vertId, int neighborVertId);
	/**
	 * @brief�������еĶ�������
	 */
	void resetAllVerts(unsigned int startId);
	/**
	 * @brief ������һ��ȷ�ϵĶ���
	 */
	bool findNextClosedVert(float& minDist, int& minIdx, std::vector<int>& closedVec);
	/**
	 * @brief �޸����·��
	 */
	void modifyVertsDist(float& minDist, int& minIdx);
	/**
	 * @brief ���Ҷ����ھ� Id ����
	 */
	void findNeighborVertIdArr(int vertId);

public:
	MGraph();
	~MGraph();

	Vertex* getVertexById(int vertId);
	const VertVector& getVerts() const;

	Vertex* getVert(int id);
	size_t getVertsCount();
	void init(int xCount, int yCount);
	// ת������� Id ����������
	void convIdToXY(int vertId, int* x, int* y);
	int convXYToVertId(int x, int y);
	// �Ƿ����赲����
	bool isInStopPt(int nx, int ny);
	/**
	 * @brief �ھӸ��ӳɱ�
	 * @param vertId ��ʼ���� Id
	 * @Param neighborVertId �ھӶ��� Id
	 *	5	6	7
	 *	4		0
	 *	3	2	1
	 */
	float adjacentCost(int vertId, int neighborVertId);
	/**
	 * @brief ���һ���赲��
	 */
	void addStopPoint(int nx, int ny, StopPoint* pStopPoint);

	// Dijkstra �㷨��Ҫ������
	std::list<Vertex*>& getShortestPath(int startId, int endId);
	std::list<Vertex*>& buildPath(Vertex *endVert);

	void initVerts(unsigned int startId, unsigned int endId);
	bool checkFail(Vertex *endVert);			// ����Ƿ�ʧ��
	/**
	 * @brief ��ȡ���·��
	 */
	std::list<Vertex*>& getPath();
};

#endif