#include "MExportSkeleton.h"
#include "AWD.h"
#include "tinyxml2.h"
#include "MSkeleton.h"
#include "AppFrame.h"
#include "ProgOptions.h"

#include <string>

void MExportSkeleton::exportSkeleton(AWD* pAwd)
{
	std::string fullPath = g_pAppFrame->getpProgOptions()->getinFileFullPath().c_str();
	tinyxml2::XMLDocument* pXMLDocument = new tinyxml2::XMLDocument;
	tinyxml2::XMLElement* pSkeletonElement = pXMLDocument->NewElement("skeleton");
	pXMLDocument->InsertEndChild(pSkeletonElement);

	tinyxml2::XMLElement* bones = pXMLDocument->NewElement("bones");
	pSkeletonElement->InsertEndChild(bones);

	AWDBlockList * skeletonBlocks = pAwd->get_skeleton_blocks();
	AWDSkeleton *skelBlock;
	AWDBlockIterator it(skeletonBlocks);

	while ((skelBlock = (AWDSkeleton *)it.next()) != NULL) 
	{
		MSkeleton* pMSkeleton = new MSkeleton(skelBlock);
		pMSkeleton->buildBoneList();
		pMSkeleton->buildboneXmlList(bones, pXMLDocument);
	}

	tinyxml2::XMLError ret = pXMLDocument->SaveFile(fullPath.c_str());
	if (tinyxml2::XML_NO_ERROR == ret)
	{
		// ³É¹¦
	}
	else
	{
		// Ê§°Ü
	}
}