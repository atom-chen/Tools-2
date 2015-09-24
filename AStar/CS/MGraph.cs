using System;
using System.Collections.Generic;

namespace SDK.Lib
{
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
        Closed,         // ����Ѿ�ȷ���˶��㣬�������״̬
        Open,           // ����Ѿ����������ǻ�û��ȷ�Ͼ������״̬
        Unknown         // �����״̬�������״̬
    }

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
            m_vertsIdVec = new List<int>();
            reset();
        }

        public void dispose()
        {
            if (m_pStopPoint != null)
            {
                m_pStopPoint = null;
            }
        }

        public void reset()
        {
            //m_id = 0;
            m_state = State.Unknown;
            m_nearestVert = null;
            m_distance = float.MaxValue;
            m_bNeighborValid = false;
            m_pStopPoint = null;
            m_vertsIdVec.Clear();
        }

        public void setNeighborVertsId(int[] neighborVertIdArr, int len = 8)
        {
            m_vertsIdVec.Clear();
            m_bNeighborValid = true;
            for (int idx = 0; idx < len; ++idx)
            {
                if (neighborVertIdArr[idx] != -1)
                {
                    m_vertsIdVec.Add(neighborVertIdArr[idx]);
                }
            }
        }
    }

    public partial class MGraph
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
        protected PathCache m_pathCache;

        // ��ȡ�ھ���Ϣ�ĸ�������
        protected int[] m_dx;
        protected int[] m_dy;
        protected float[] m_cost;

        public MGraph()
        {
            m_vertsVec = new List<Vertex>();
            m_pathList = new List<Vertex>();
            m_neighborVertIdArr = new int[8];
            m_closedVec = new List<int>();
            m_pathCache = new PathCache();


            m_dx = new int[8] { -1, 0, 1, -1, 1, -1, 0, 1 };
            m_dy = new int[8] { -1, -1, 1, 0, 0, 1, 1, 1 };
            m_cost = new float[8] { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
        }

        public void dispose()
        {

        }


        public Vertex getVertexById(int vertId)
        {
            if (vertId < m_vertsVec.Count)
            {
                return m_vertsVec[vertId];
            }

            return null;
        }

        public List<Vertex> getVertsVec()
        {
            return m_vertsVec;
        }

        public int getVertsCount()
        {
            return m_vertsVec.Count;
        }

        public void init(int xCount, int yCount, float gridWidth, float gridHeight)
        {
            m_xCount = xCount;
            m_yCount = yCount;
            m_gridWidth = gridWidth;
            m_gridHeight = gridHeight;

            m_vertsCount = m_xCount * m_yCount;

            int idx = 0;
            Vertex pVertex = null;

            for (idx = 0; idx < m_vertsCount; ++idx)
            {
                pVertex = new Vertex();
                m_vertsVec.Add(pVertex);
                pVertex.reset();
                pVertex.m_id = idx;
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
                if (m_vertsVec[index].m_pStopPoint != null)         // ������赲��
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
        protected float adjacentCost(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;
            float neighborCost = float.MaxValue;            // Ĭ�������ֵ

            if (vertId == neighborVertId)       // ������Լ����ͷ��� 0
            {
                return 0;
            }

            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);
            if (isInStopPt(xNeighbor, yNeighbor))       // ����ھ����赲����
            {
                return neighborCost;
            }

            convVertIdToXY(vertId, ref x, ref y);
            if (Math.Abs((long)(xNeighbor - x)) > 1 || Math.Abs((long)(yNeighbor - y)) > 1) // ������� 1 ����˵���м��м��������ֱ�ӵ���
            {
                return neighborCost;
            }

            int nx = 0;
            int ny = 0;

            for (int i = 0; i < 8; ++i)
            {
                nx = x + m_dx[i];
                ny = y + m_dy[i];

                if (convXYToVertId(nx, ny) == neighborVertId)       // ����������ھ�
                {
                    // �϶������赲���У���Ϊ������赲���У������Ѿ��ж���
                    if (isHorizontalOrVerticalNeighbor(vertId, neighborVertId))     // �����ˮƽ���ߴ�ֱ����б��
                    {
                        neighborCost = m_cost[i];
                    }
                    else
                    {
                        // ��Ҫ�ж�б���ϵ���һ��б�ߵ����������Ƿ����赲��
                        if (!isInStopPt(x, yNeighbor) && !isInStopPt(xNeighbor, y))     // ����Խ����ϵ��������Ӷ������赲��
                        {
                            neighborCost = m_cost[i];
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

        protected bool isHorizontalOrVerticalNeighbor(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;

            convVertIdToXY(vertId, ref x, ref y);
            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);

            if ((Math.Abs((long)(xNeighbor - x)) == 1 && Math.Abs((long)(yNeighbor - y)) == 0) ||
                (Math.Abs((long)(xNeighbor - x)) == 0 && Math.Abs((long)(yNeighbor - y)) == 1))
            {
                return true;
            }

            return false;
        }

        protected bool isHorizontalNeighbor(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;

            convVertIdToXY(vertId, ref x, ref y);
            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);

            if ((Math.Abs((long)(xNeighbor - x)) == 1 && Math.Abs((long)(yNeighbor - y)) == 0))
            {
                return true;
            }

            return false;
        }

        protected bool isVerticalNeighbor(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;

            convVertIdToXY(vertId, ref x, ref y);
            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);

            if ((Math.Abs((long)(xNeighbor - x)) == 0 && Math.Abs((long)(yNeighbor - y)) == 1))
            {
                return true;
            }

            return false;
        }

        protected bool isSlashNeighbor(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;

            convVertIdToXY(vertId, ref x, ref y);
            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);

            if ((Math.Abs((long)(xNeighbor - x)) == 1 && Math.Abs((long)(yNeighbor - y)) == 1))         // б��
            {
                return true;
            }

            return false;
        }

        protected bool isNeighbor(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;

            convVertIdToXY(vertId, ref x, ref y);
            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);

            if ((Math.Abs((long)(xNeighbor - x)) == 1 && Math.Abs((long)(yNeighbor - y)) == 0) ||       // ˮƽ
                (Math.Abs((long)(xNeighbor - x)) == 0 && Math.Abs((long)(yNeighbor - y)) == 1) ||       // ��ֱ
                (Math.Abs((long)(xNeighbor - x)) == 1 && Math.Abs((long)(yNeighbor - y)) == 1))         // б��
            {
                return true;
            }

            return false;
        }

        protected bool isBackSlashStopPoint(int vertId, int neighborVertId)
        {
            int x = 0;
            int y = 0;
            int xNeighbor = 0;
            int yNeighbor = 0;

            convVertIdToXY(vertId, ref x, ref y);
            convVertIdToXY(neighborVertId, ref xNeighbor, ref yNeighbor);

            if (isInStopPt(x, yNeighbor) || isInStopPt(xNeighbor, y))
            {
                return true;
            }

            return false;
        }

        protected void findNeighborVertIdArr(int vertId)
        {
            int x = 0;
            int y = 0;
            convVertIdToXY(vertId, ref x, ref y);

            int nx = 0;
            int ny = 0;

            // ���� 8 ���ھӶ���
            for (int i = 0; i < 8; ++i)
            {
                nx = x + m_dx[i];
                ny = y + m_dy[i];

                if (nx >= 0 && nx < m_xCount &&
                    ny >= 0 && ny < m_yCount)       // ����ھӶ����ڷ�Χ��
                {
                    if (!isInStopPt(nx, ny))        // ��������赲����
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

        protected void setNeighborInvalidByVertId(int vertId)
        {
            // ��Ҫ�޸��ھ���������������������ھ�
            if (!m_vertsVec[vertId].m_bNeighborValid)
            {
                findNeighborVertIdArr(vertId);
                m_vertsVec[vertId].setNeighborVertsId(m_neighborVertIdArr);
            }

            for (int neighborIdx = 0; neighborIdx < m_vertsVec[vertId].m_vertsIdVec.Count; ++neighborIdx)
            {
                m_vertsVec[m_vertsVec[vertId].m_vertsIdVec[neighborIdx]].m_bNeighborValid = false;
            }
        }

        public Vertex getVertexByPos(float fx, float fy)
        {
            int ix = (int)(fx / m_gridWidth);
            int iy = (int)(fx / m_gridHeight);

            return m_vertsVec[convXYToVertId(ix, iy)];
        }

        public void getVertexCenterByPos(float fx, float fy, ref float centerX, ref float centerY)
        {
            int ix = (int)(fx / m_gridWidth);
            int iy = (int)(fx / m_gridHeight);

            centerX = ix * m_gridWidth + m_gridWidth / 2;
            centerY = ix * m_gridHeight + m_gridHeight / 2;
        }
    }
}