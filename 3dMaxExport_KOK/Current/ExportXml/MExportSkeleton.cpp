#include "MExportSkeleton.h"
#include "AWD.h"
#include "tinyxml2.h"
#include "MSkeleton.h"

void MExportSkeleton::exportSkeleton(char* fullPath, AWD* pAwd)
{
	tinyxml2::XMLDocument* pXMLDocument = new tinyxml2::XMLDocument;
	tinyxml2::XMLElement* pSkeletonElement = pXMLDocument->NewElement("skeleton");
	pXMLDocument->InsertFirstChild(pSkeletonElement);

	AWDBlockList * skeletonBlocks = pAwd->get_skeleton_blocks();
	AWDSkeleton *skelBlock;
	AWDBlockIterator it(skeletonBlocks);

	while ((skelBlock = (AWDSkeleton *)it.next()) != NULL) 
	{
		MSkeleton* pMSkeleton = new MSkeleton(skelBlock);
		pMSkeleton->buildBoneList();
	}
}