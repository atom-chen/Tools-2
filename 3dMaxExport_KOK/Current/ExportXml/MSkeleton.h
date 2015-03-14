#ifndef __MSkeleton_H_
#define __MSkeleton_H_

#include <vector>
#include "MTypeDefine.h"
#include "tinyxml2.h"

class AWDSkeletonJoint;

class MSkeletonJoint
{
protected:
	MSkeletonJoint* m_pParentMSkeletonJoint;
	AWDSkeletonJoint* m_pAWDSkeletonJoint;
	std::vector<MSkeletonJoint*> m_MSkeletonJointVec;
	MMat3x3* m_pRSMat;
	MMVec3* m_pTVec;

public:
	MSkeletonJoint(AWDSkeletonJoint* pAWDSkeleton, MSkeletonJoint* pParent);
	void buildJointChildList();
	void buildMatrix();
	void buildboneXml(tinyxml2::XMLElement* bonesElem, tinyxml2::XMLDocument* pXMLDocument, int boneIdx);

	MMVec3& getPos();
	MQuat getRot();
};

class AWDSkeleton;

class MSkeleton
{
protected:
	AWDSkeleton* m_pAWDSkeleton;
	MSkeletonJoint* m_pRootMSkeletonJoint;

public:
	MSkeleton(AWDSkeleton* pAWDSkeleton);
	void buildBoneList();
	void buildboneXmlList(tinyxml2::XMLElement* bonesElem, tinyxml2::XMLDocument* pXMLDocument);
};


#endif