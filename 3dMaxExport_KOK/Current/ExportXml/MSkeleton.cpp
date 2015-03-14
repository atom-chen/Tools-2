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

	// 局部空间信息
	awd_float64 *pbind_mtx = m_pAWDSkeletonJoint->get_bind_mtx();

	int col = 0;
	int row = 0;
	int oneIdx = 0;

	// 由于矩阵是按照列存储的，因此这里也先访问列，前 3 列是 3 个坐标轴，第 4 列是偏移
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

// 位置偏移
MMVec3& MSkeletonJoint::getPos()
{
	return (*m_pTVec);
}

MQuat MSkeletonJoint::getRot()
{
	return glm::toQuat<float, glm::mediump>(*m_pRSMat);
}

void MSkeletonJoint::buildboneXml(tinyxml2::XMLElement* bonesElem, tinyxml2::XMLDocument* pXMLDocument, int boneIdx)
{
	tinyxml2::XMLElement* boneElem = pXMLDocument->NewElement("bone");
	bonesElem->InsertEndChild(boneElem);
	boneElem->SetAttribute("id", boneIdx);
	boneElem->SetAttribute("name", m_pAWDSkeletonJoint->get_name());

	tinyxml2::XMLElement* posElem = pXMLDocument->NewElement("position");
	boneElem->InsertEndChild(posElem);
	posElem->SetAttribute("x", (*m_pTVec)[0]);
	posElem->SetAttribute("y", (*m_pTVec)[1]);
	posElem->SetAttribute("z", (*m_pTVec)[2]);

	tinyxml2::XMLElement* rotElem = pXMLDocument->NewElement("rotation");
	boneElem->InsertEndChild(rotElem);
	MQuat pMQuat = getRot();
	rotElem->SetAttribute("angle", pMQuat.w);

	tinyxml2::XMLElement* axisElem = pXMLDocument->NewElement("axis");
	rotElem->InsertEndChild(axisElem);
	axisElem->SetAttribute("x", pMQuat.x);
	axisElem->SetAttribute("y", pMQuat.y);
	axisElem->SetAttribute("z", pMQuat.z);

	++boneIdx;

	AWDSkeletonJoint* child = m_pAWDSkeletonJoint->get_first_child();
	while (child)
	{
		MSkeletonJoint* pMSkeletonJoint = new MSkeletonJoint(child, this);
		pMSkeletonJoint->buildboneXml(bonesElem, pXMLDocument, boneIdx);
		child = child->next;
	}
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

void MSkeleton::buildboneXmlList(tinyxml2::XMLElement* bonesElem, tinyxml2::XMLDocument* pXMLDocument)
{
	m_pRootMSkeletonJoint->buildboneXml(bonesElem, pXMLDocument, 0);
}