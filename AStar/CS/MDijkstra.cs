using System;
using System.Collections.Generic;

namespace SDK.Lib
{
    public partial class MGraph
    {
        protected void buildPath(Vertex endVert)
        {
            Vertex vert = endVert;
            while (vert != null)
            {
                m_pathList.Insert(0, vert);
                vert = vert.m_nearestVert;
            }
            m_pathList.Insert(0, m_startVert);      // ������Ķ���Ž�ȥ
        }

        protected void initVerts(int startId, int endId)
        {
            m_startVert = null;
            m_endVert = null;

            int nx = 0;
            int ny = 0;

            convVertIdToXY(startId, ref nx, ref ny);
            if (nx >= 0 && nx < m_xCount
                && ny >= 0 && ny < m_yCount)
            {
                m_startVert = m_vertsVec[startId];
            }

            convVertIdToXY(endId, ref nx, ref ny);
            if (nx >= 0 && nx < m_xCount
                && ny >= 0 && ny < m_yCount)
            {
                m_endVert = m_vertsVec[endId];
            }

            if (m_startVert == null || m_endVert == null)
            {
                throw new Exception("Failed to find the start/end node(s)!");
            }


            m_startVert.m_distance = 0;
        }

        protected void resetAllVerts(int startId)
        {
            Vertex pVert = null;
            // ��ʼ������
            for (int vertIdx = 0; vertIdx < m_vertsCount; ++vertIdx)
            {
                pVert = m_vertsVec[vertIdx];
                pVert.m_state = State.Unknown;    // ȫ�������ʼ��Ϊδ֪�Զ�·��״̬
                pVert.m_distance = adjacentCost(startId, vertIdx); //���� startId �������ߵĶ������Ȩֵ
                pVert.m_nearestVert = null;    // ��ʼ��·����ǰһ������
            }

            m_startVert.m_distance = 0;    //  startId �� startId ·��Ϊ0
            m_startVert.m_state = State.Closed;    // m_startVert->m_state ��ʾ startId �� startId ����Ҫ��·�����Ѿ���ӵ�ȷ�϶�������
        }

        protected bool findNextClosedVert(ref float minDist, ref int minIdx, List<int> closedVec)
        {
            Vertex pVert = null;
            int closedIdx = 0;
            int neighborVertIdx = 0;
            minDist = float.MaxValue;    // ��ǰ��֪�� startId �����������
            bool bFindNextClosedVert = false;

            // ֻҪ������Χ 8 ������Ϳ����ˣ���Ϊ����Ѱ·ֻ���Ǻ��Լ���Χ�� 8 �����Ӳ���Ȩ�أ��������ĸ�����û��Ȩ�ص�
            for (closedIdx = 0; closedIdx < closedVec.Count; ++closedIdx)
            {
                if (!m_vertsVec[closedVec[closedIdx]].m_bNeighborValid)     // ����ھ���������Ч��
                {
                    findNeighborVertIdArr(closedVec[closedIdx]);
                    m_vertsVec[closedVec[closedIdx]].setNeighborVertsId(m_neighborVertIdArr);
                }

                for (neighborVertIdx = 0; neighborVertIdx < m_vertsVec[closedVec[closedIdx]].m_vertsIdVec.Count; ++neighborVertIdx)
                {
                    pVert = m_vertsVec[m_vertsVec[closedVec[closedIdx]].m_vertsIdVec[neighborVertIdx]];
                    if (pVert.m_state != State.Closed && pVert.m_distance < minDist)
                    {
                        minDist = pVert.m_distance; // w������ startId �������
                        minIdx = pVert.m_id;
                        bFindNextClosedVert = true;             // ˵�����ҵ���
                    }
                }
            }

            return bFindNextClosedVert;
        }

        protected void modifyVertsDist(ref float minDist, ref int minIdx)
        {
            int neighborVertIdx = 0;
            Vertex pVert = null;

            // ֻ��Ҫ�������¼��� closed �Ķ�����ھӶ���
            if (!m_vertsVec[minIdx].m_bNeighborValid)       // ����ھ���������Ч��
            {
                findNeighborVertIdArr(minIdx);
                m_vertsVec[minIdx].setNeighborVertsId(m_neighborVertIdArr);
            }
            for (neighborVertIdx = 0; neighborVertIdx < m_vertsVec[minIdx].m_vertsIdVec.Count; ++neighborVertIdx) // ������ǰ���·������
            {
                pVert = m_vertsVec[m_vertsVec[minIdx].m_vertsIdVec[neighborVertIdx]];
                // �������V�����·������������·���ĳ��ȶ̵Ļ�
                if (pVert.m_state != State.Closed && (minDist + adjacentCost(minIdx, pVert.m_id) < pVert.m_distance))
                {
                    // ˵���ҵ�����̵�·�����޸�D[w] �� p[w]
                    pVert.m_distance = minDist + adjacentCost(minIdx, pVert.m_id); // �޸ĵ�ǰ·������
                    pVert.m_nearestVert = m_vertsVec[minIdx];
                }
            }
        }

        public List<Vertex> getShortestPath()
        {
            return m_pathList;
        }

        public void createShortestPath(int startId, int endId)
        {
            m_pathList.Clear();
            m_closedVec.Clear();

            initVerts(startId, endId);

            int openVertIdx = 0;        // ��δȷ����ӵ������еĶ������������
            int minIdx = 0;
            float minDist = 0;
            Vertex pVert = null;
            bool bFindShortestPath = false;

            resetAllVerts(startId);

            m_closedVec.Add(startId);

            // �ܹ��� nVerts �����㣬�� startId ���Ѿ�ȷ�ϣ�ֻ��Ҫȷ��ʣ�µ� nVerts - 1 �Ϳ�����
            for (openVertIdx = 1; openVertIdx < m_vertsCount; ++openVertIdx)
            {
                // Ҫ���� m_closedVec �еĵ㣬����ֻ���� minIdx �����ĵ㣬������Щ·����ʼȨ�رȽ�С������Ȩ�رȽϴ󣬵�����Щ·����ʼȨ�رȽϴ󣬺���Ȩ�رȽ�С
                if (findNextClosedVert(ref minDist, ref minIdx, m_closedVec))   // ������ҵ�����һ����̵�δȷ�ϵ�����
                {
                    // ע����ʼ����͵ڶ�������֮����û�� m_nearestVert �������Ҫ�ֹ�����һ������ŵ�·���б���ȥ
                    pVert = m_vertsVec[minIdx];
                    pVert.m_state = State.Closed; // ��Ŀǰ�ҵ�������Ķ�����Ϊ State::Closed 
                    m_closedVec.Add(minIdx);

                    modifyVertsDist(ref minDist, ref minIdx);
                }
                else                // ����Ҳ�����һ����С�Ķ�����������ֱ���˳��ɣ�û����̾���
                {
                    bFindShortestPath = false;
                    break;
                }

                if (minIdx == endId)            // ������ҵ�
                {
                    bFindShortestPath = true;
                    break;
                }
            }

            if (bFindShortestPath)
            {
                buildPath(m_endVert);   // ����·���б�
                convVertList2VertIdVec(m_pathCache.getAndAddPathCache(startId, endId).m_vertsIdVec);        // ����Ŀ¼
            }
        }

        public List<Vertex> getOrCreateShortestPath(int startId, int endId)
        {
            if (m_pathList.Count == 0)
            {
                createShortestPath(startId, endId);
            }

            return m_pathList;
        }

        protected void convVertIdVec2VertList(List<int> vertsIdVec)
        {
            m_pathList.Clear();
            foreach (var vertId in vertsIdVec)
            {
                m_pathList.Add(m_vertsVec[vertId]);
            }
        }

        protected void convVertList2VertIdVec(List<int> vertsIdVec)
        {
            foreach (var vert in m_pathList)
            {
                vertsIdVec.Add(vert.m_id);
            }
        }

        public bool isPathCacheValid(int startId, int endId)
        {
            return m_pathCache.isPathValid(startId, endId);
        }

        public List<Vertex> getShortestPathFromPathCache(int startId, int endId)
        {
            if (isPathCacheValid(startId, endId))
            {
                convVertIdVec2VertList(m_pathCache.getPathCache(startId, endId).m_vertsIdVec);
            }
            else
            {
                m_pathList.Clear();
            }

            return m_pathList;
        }

        public void clearPath()
        {
            m_pathList.Clear();
        }

        public void clearAllStopPoint()
        {
            foreach (var vert in m_vertsVec)
            {
                if (vert.m_pStopPoint != null)      // ����ͨ�� m_id2StopPtMap[idx] ����������ݣ���������ж�
                {
                    setNeighborInvalidByVertId(vert.m_id);
                    vert.m_pStopPoint = null;
                }
            }
        }
    }
}