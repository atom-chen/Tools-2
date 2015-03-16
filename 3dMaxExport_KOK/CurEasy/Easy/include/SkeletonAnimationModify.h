#ifndef _SKELETONANIMATIONMODIFY_H
#define _SKELETONANIMATIONMODIFY_H

#include "ExPrerequisites.h"
#include <vector>
#include "AutoDefine.h"
#include <string>

/**
 * @brief Skeleton Animation Modify data
 */
namespace EasyOgreExporter
{
	// һ������֡������
	class Modify_ClipFrameItem
	{
	public:
		std::string m_name;
		int m_startFrame;
		int m_endFrame;
	};

	class SkeletonAnimationModify
	{
	protected:
		IGameModifier* m_pGameModifie;
		std::vector<Modify_ClipFrameItem*> m_clipFrameItemVec;

	protected:
		void initModifyData();		// ��ȡ Modify �е�����
		void cleanClipItemVec();	// �ͷ� Vector ��Դ

	public:
		SkeletonAnimationModify(IGameModifier* pGameModifier);
		~SkeletonAnimationModify();

		DECLARE_SET_GET_RETPFUNC(std::vector<Modify_ClipFrameItem*>, clipFrameItemVec);
		void ReadAnimationClipsBlock(IParamBlock2 *pb);
	};
}	//end namespace

#endif
