#include "name.h"
#include "MSkeleton.h"
#include "skeleton.h"
#include "glm/gtx/quaternion.hpp"

MSkeletonJoint::MSkeletonJoint(AWDSkeletonJoint* pAWDSkeletonJoint, MSkeletonJoint* pParent)
{
	m_pParentMSkeletonJoint = pParent;
	m_pAWDSkeletonJoint = pAWDSkeletonJoint;
}

void MSkeletonJoint::buildJointChildList()
{
	buildMatrix();

	AWDSkeletonJoint* child = m_pAWDSkeletonJoint->get_first_child();
	while (child) 
	{
		MSkeletonJoint* pMSkeletonJoint = new MSkeletonJoint(child, this);
		m_MSkeletonJointVec.push_back(pMSkeletonJoint);
		pMSkeletonJoint->buildJointChildList();
		child = child->next;
	}
}

void MSkeletonJoint::buildMatrix()
{
	m_pRSMat = new MMat3x3;
	m_pTVec = new MMVec3;

	// �ֲ��ռ���Ϣ
	awd_float64 *pbind_mtx = m_pAWDSkeletonJoint->get_bind_mtx();

	int col = 0;
	int row = 0;
	int oneIdx = 0;

	// ���ھ����ǰ����д洢�ģ��������Ҳ�ȷ����У�ǰ 3 ���� 3 �������ᣬ�� 4 ����ƫ��
	for (; col < 3; ++row)
	{
		for (; row < 3; ++col)
		{
			oneIdx = col * 3 + row;
			
			(*m_pRSMat)[col][row] = (float)pbind_mtx[oneIdx];
		}
	}

	for (oneIdx = 9; oneIdx < 12; ++oneIdx)
	{
		(*m_pTVec)[oneIdx - 9] = (float)pbind_mtx[oneIdx];
	}
}

// λ��ƫ��
MMVec3& MSkeletonJoint::getPosOffset()
{
	return (*m_pTVec);
}

MQuat MSkeletonJoint::getRot()
{
	return glm::toQuat<float, glm::mediump>(*m_pRSMat);
}

MSkeleton::MSkeleton(AWDSkeleton* pAWDSkeleton)
{
	m_pAWDSkeleton = pAWDSkeleton;
}

void MSkeleton::buildBoneList()
{
	m_pRootMSkeletonJoint = new MSkeletonJoint(m_pAWDSkeleton->get_root_joint(), nullptr);
	m_pRootMSkeletonJoint->buildJointChildList();
}
