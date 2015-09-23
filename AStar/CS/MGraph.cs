// �赲��
public class StopPoint
{
	public StopPoint()
    {

    }

    public void dispose()
    {

    }
}

// ��ǰ�����״̬
public enum State
{
    Closed,			// ����Ѿ�ȷ���˶��㣬�������״̬
	Open,			// ����Ѿ����������ǻ�û��ȷ�Ͼ������״̬
	Unknown			// �����״̬�������״̬
};

// ��������
public class Vertex
{
    public int m_id;
    public State m_state;
    public Vertex m_nearestVert;
    public float m_distance;
    public bool m_bNeighborValid;      // �ھ������Ƿ���Ч����Ϊ���ܶ�̬�޸��赲��
    public List<int> m_vertsIdVec;          // �����ھӶ��� Id�������ֵֻ����ʹ�õ�ʱ��Żᶯ̬���ɣ���ʼ����ʱ�򲢲�����
    public StopPoint m_pStopPoint;            // �赲����Ϣ

    public Vertex()
    {
       reset();
    }

    public void dispose()
    {
        if (m_pStopPoint)
        {
            delete m_pStopPoint;
            m_pStopPoint = nullptr;
        }
    }

    public void reset()
    {
        //m_id = 0;
        m_state = State::Unknown;
        m_nearestVert = null;
        m_distance = float.MaxValue;
        m_bNeighborValid = false;
        m_pStopPoint = null;
        m_vertsIdVec.clear();
    }

    public void setNeighborVertsId(int[] neighborVertIdArr, int len)
    {
        m_vertsIdVec.clear();
        m_bNeighborValid = true;
        for (int idx = 0; idx < len; ++idx)
        {
            if (neighborVertIdArr[idx] != -1)
            {
                m_vertsIdVec.push_back(neighborVertIdArr[idx]);
            }
        }
    }
}

public class MGraph
{
	protected List<Vertex> m_vertsVec;      // ���еĶ��㣬������ʱ�����еĶ���ȫ��������������Ҫ��ʱ���ٴ����������Ҫ��ʱ���ٴ���������Ҫ�����ж�
    protected int m_vertsCount;           // �����ܹ�����
    protected int m_xCount;               // X ��������
    protected int m_yCount;               // Y ��������
    protected float m_gridWidth;          // ���ӿ��
    protected float m_gridHeight;         // ���Ӹ߶�

    // Dijkstra �㷨��Ҫ������
    protected Vertex m_startVert;
    protected Vertex m_endVert;

    // ����·���б�
    protected List<Vertex> m_pathList;  // ʹ�� List ����Ҫ��ʹ�� push_front ����ӿ�
                                        // ��������Ҫ�õ� 8 ���ھӶ�������
    protected int[] m_neighborVertIdArr;
    protected List<int> m_closedVec;   // �Ѿ�ȷ�ϵĶ����б�

    // ·�������б�
    PathCache m_pathCache;


    public MGraph()
    {
        m_neighborVertIdArr = new int[8];
    }

    public void dispose()
    {

    }


    public Vertex getVertexById(int vertId)
    {
	    if (vertId < m_vertsVec.size())
	    {
		    return m_vertsVec[vertId];
	    }

	    return nullptr;
    }

    public List<Vertex> getVertsVec()
    {
	    return m_vertsVec;
    }

    public int getVertsCount()
    {
	    return m_vertsVec.size();
    }

    public void init(int xCount, int yCount, float gridWidth, float gridHeight)
    {
	    m_xCount = xCount;
	    m_yCount = yCount;
	    m_gridWidth = gridWidth;
	    m_gridHeight = gridHeight;

	    m_vertsCount = m_xCount * m_yCount;

	    int idx = 0;
	    Vertex* pVertex = nullptr;

	    for (idx = 0; idx < m_vertsCount; ++idx)
	    {
		    pVertex = new Vertex();
		    m_vertsVec.push_back(pVertex);
		    pVertex->reset();
		    pVertex->m_id = idx;
	    }
    }

    // ת������� Id ����������
    public void convVertIdToXY(int vertId, ref int x, ref int y)
    {
	    y = vertId / m_xCount;
	    x = vertId - y * m_xCount;
    }

    public int convXYToVertId(int x, int y)
    {
	    return (y * m_xCount + x);
    }

    // �Ƿ����赲����
    public bool isInStopPt(int nx, int ny)
    {
	    if (nx >= 0 && nx < m_xCount
		    && ny >= 0 && ny < m_yCount)
	    {
		    int index = ny * m_xCount + nx;
		    if (m_vertsVec[index]->m_pStopPoint)			// ������赲��
		    {
			    return true;
		    }
	    }

	    return false;
    }

    /**
    * @brief �ھӸ��ӳɱ�
    * @param vertId ��ʼ���� Id
    * @Param neighborVertId �ھӶ��� Id
    *	0	1	2
    *	3		4
    *	5	6	7
    */
    public float adjacentCost(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    float neighborCost = float.MaxValue;            // Ĭ�������ֵ
        const int[] dx = new int[8] { -1, 0, 1, -1, 1, -1, 0, 1 };
        const int[] dy = new int[8] { -1, -1, 1, 0, 0, 1, 1, 1 };
        const float[] cost = new float[8]{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	    if (vertId == neighborVertId)		// ������Լ����ͷ��� 0
	    {
		    return 0;
	    }

	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);
	    if (isInStopPt(xNeighbor, yNeighbor))		// ����ھ����赲����
	    {
		    return neighborCost;
	    }

	    convVertIdToXY(vertId, x, y);
	    if (std::abs((long)(xNeighbor - x)) > 1 || std::abs((long)(yNeighbor - y)) > 1)	// ������� 1 ����˵���м��м��������ֱ�ӵ���
	    {
		    return neighborCost;
	    }

	    int nx = 0;
	    int ny = 0;

	    for (int i = 0; i<8; ++i)
	    {
		    nx = x + dx[i];
		    ny = y + dy[i];

		    if (convXYToVertId(nx, ny) == neighborVertId)		// ����������ھ�
		    {
			    // �϶������赲���У���Ϊ������赲���У������Ѿ��ж���
			    if (isHorizontalOrVerticalNeighbor(vertId, neighborVertId))		// �����ˮƽ���ߴ�ֱ����б��
			    {
				    neighborCost = cost[i];
			    }
			    else
			    {
				    // ��Ҫ�ж�б���ϵ���һ��б�ߵ����������Ƿ����赲��
				    if (!isInStopPt(x, yNeighbor) && !isInStopPt(xNeighbor, y))		// ����Խ����ϵ��������Ӷ������赲��
				    {
					    neighborCost = cost[i];
				    }
			    }

			    break;
		    }
	    }

	    return neighborCost;
    }

    public void addStopPoint(int nx, int ny, StopPoint pStopPoint)
    {
	    int vertId = convXYToVertId(nx, ny);
	    m_vertsVec[vertId].m_pStopPoint = pStopPoint;

	    setNeighborInvalidByVertId(vertId);
    }

    public bool isHorizontalOrVerticalNeighbor(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    convVertIdToXY(vertId, x, y);
	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	    if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||
		    (std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1))
	    {
		    return true;
	    }

	    return false;
    }

    public bool isHorizontalNeighbor(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    convVertIdToXY(vertId, x, y);
	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	    if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0))
	    {
		    return true;
	    }

	    return false;
    }

    public bool isVerticalNeighbor(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    convVertIdToXY(vertId, x, y);
	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	    if ((std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1))
	    {
		    return true;
	    }

	    return false;
    }

    public bool isSlashNeighbor(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    convVertIdToXY(vertId, x, y);
	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	    if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 1))			// б��
	    {
		    return true;
	    }

	    return false;
    }

    public bool isNeighbor(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    convVertIdToXY(vertId, x, y);
	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	    if ((std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 0) ||		// ˮƽ
		    (std::abs((long)(xNeighbor - x)) == 0 && std::abs((long)(yNeighbor - y)) == 1) ||		// ��ֱ
		    (std::abs((long)(xNeighbor - x)) == 1 && std::abs((long)(yNeighbor - y)) == 1))			// б��
	    {
		    return true;
	    }

	    return false;
    }

    public bool isBackSlashStopPoint(int vertId, int neighborVertId)
    {
	    int x, y;
	    int xNeighbor, yNeighbor;
	    convVertIdToXY(vertId, x, y);
	    convVertIdToXY(neighborVertId, xNeighbor, yNeighbor);

	    if (isInStopPt(x, yNeighbor) || isInStopPt(xNeighbor, y))
	    {
		    return true;
	    }

	    return false;
    }

    public void findNeighborVertIdArr(int vertId)
    {
	    int x, y;
	    convVertIdToXY(vertId, x, y);

	    const int[] dx = new int[8]{ -1, 0, 1, -1, 1, -1, 0, 1 };
	    const int[] dy = new int[8]{ -1, -1, 1, 0, 0, 1, 1, 1 };

	    int nx = 0;
	    int ny = 0;

	    // ���� 8 ���ھӶ���
	    for (int i = 0; i < 8; ++i)
	    {
		    nx = x + dx[i];
		    ny = y + dy[i];

		    if (nx >= 0 && nx < m_xCount &&
			    ny >= 0 && ny < m_yCount)		// ����ھӶ����ڷ�Χ��
		    {
			    if (!isInStopPt(nx, ny))		// ��������赲����
			    {
				    m_neighborVertIdArr[i] = convXYToVertId(nx, ny);
			    }
			    else
			    {
				    m_neighborVertIdArr[i] = -1;
			    }
		    }
		    else
		    {
			    m_neighborVertIdArr[i] = -1;
		    }
	    }
    }

    public void setNeighborInvalidByVertId(int vertId)
    {
	    // ��Ҫ�޸��ھ���������������������ھ�
	    if (!m_vertsVec[vertId]->m_bNeighborValid)
	    {
		    findNeighborVertIdArr(vertId);
		    m_vertsVec[vertId]->setNeighborVertsId(m_neighborVertIdArr);
	    }

	    for (int neighborIdx = 0; neighborIdx < m_vertsVec[vertId]->m_vertsIdVec.size(); ++neighborIdx)
	    {
		    m_vertsVec[m_vertsVec[vertId]->m_vertsIdVec[neighborIdx]]->m_bNeighborValid = false;
	    }
    }

    public Vertex* getVertexByPos(float fx, float fy)
    {
	    int ix = fx / m_gridWidth;
	    int iy = fx / m_gridHeight;

	    return m_vertsVec[convXYToVertId(ix, iy)];
    }

    public void getVertexCenterByPos(float fx, float fy, ref float centerX, ref float centerY)
    {
	    int ix = fx / m_gridWidth;
	    int iy = fx / m_gridHeight;

	    m_vertsVec[convXYToVertId(ix, iy)];

	    centerX = ix * m_gridWidth + m_gridWidth / 2;
	    centerY = ix * m_gridHeight + m_gridHeight / 2;
    }
}