#include "SkeletonAnimationModify.h"
#include "UtilWrap.h"

namespace EasyOgreExporter
{
	DEFINE_SET_GET_RETPFUNC(SkeletonAnimationModify, std::vector<Modify_ClipFrameItem*>, clipFrameItemVec);

	SkeletonAnimationModify::SkeletonAnimationModify(IGameModifier* pGameModifier)
	{
		m_pGameModifie = pGameModifier;
		initModifyData();
	}

	SkeletonAnimationModify::~SkeletonAnimationModify()
	{

	}

	void SkeletonAnimationModify::cleanClipItemVec()
	{
		int idx = 0;
		for (idx = 0; idx < m_clipFrameItemVec.size(); ++idx)
		{
			delete m_clipFrameItemVec[idx];
		}
	}

	void SkeletonAnimationModify::initModifyData()
	{
		cleanClipItemVec();

		IPropertyContainer* pIPropertyContainer;
		IGameProperty* pIGameProperty;
		IParamBlock2* pIParamBlock2;

		pIPropertyContainer = m_pGameModifie->GetIPropertyContainer();	// 所有参数容器
		int numofProps = pIPropertyContainer->GetNumberOfProperties();	// 参数属性数量
		// Modify 参数在 第 0 个，总共就 1 个
		int idx = 0;
		//for (idx = 0; idx < numofProps; ++idx)	// numofProps 竟然是 5 ，5 次遍历，内容都是一样的
		//{
			//pIGameProperty = pIPropertyContainer->GetProperty(idx);	// 遍历参数属性
			pIGameProperty = pIPropertyContainer->GetProperty(0);	// 遍历参数属性，直接获取第 1 个就行了，因为就一个参数区域
			if (pIGameProperty->IsPBlock2())
			{
				pIParamBlock2 = pIGameProperty->GetMaxParamBlock2();
				ReadAnimationClipsBlock(pIParamBlock2);
			}
		//}
	}

	void SkeletonAnimationModify::ReadAnimationClipsBlock(IParamBlock2 *pb)
	{
		int numBlockparams = pb->NumParams();
		int p = 0;
		ParamID pid_names = -1;
		ParamID pid_starts = -1;
		ParamID pid_ends = -1;
		int minCount = 100000;
		for (p = 0; p < numBlockparams; p++) 
		{
			ParamID pid = pb->IndextoID(p);
			ParamDef def = pb->GetParamDef(pid);
			char * paramName = UtilWrap::W2A(def.int_name);
			if (UtilWrap::isStrEqual(paramName, "anames"))
			{
				pid_names = pid;
				if (pb->Count(pid) < minCount)
				{ 
					minCount = pb->Count(pid); 
				}
			}
			if (UtilWrap::isStrEqual(paramName, "afframes"))
			{
				pid_starts = pid;
				if (pb->Count(pid) < minCount)
				{ 
					minCount = pb->Count(pid); 
				}
			}
			if (UtilWrap::isStrEqual(paramName, "alframes"))
			{
				pid_ends = pid;
				if (pb->Count(pid) < minCount)
				{ 
					minCount = pb->Count(pid); 
				}
			}
			free(paramName);
		}
		if ((pid_names == -1) || (pid_starts == -1) || (pid_ends == -1))
		{
			minCount = 0;
		}
		if (minCount != 0)
		{
			int clipCnt = 0;
			for (clipCnt = 0; clipCnt < minCount; clipCnt++)
			{
				char * thisName_ptr = UtilWrap::W2A(pb->GetStr(pid_names, 0, clipCnt));
				int startFrame = pb->GetInt(pid_starts, 0, clipCnt);
				int endFrame = pb->GetInt(pid_ends, 0, clipCnt);
				//checking if name is unique
				Modify_ClipFrameItem * clipItem = new Modify_ClipFrameItem;
				m_clipFrameItemVec.push_back(clipItem);
				clipItem->m_name = thisName_ptr;
				clipItem->m_startFrame = startFrame * GetTicksPerFrame();		// 输出的是 tick ，不是 Frame ，里面使用的都是 tick
				clipItem->m_endFrame = endFrame * GetTicksPerFrame();

				free(thisName_ptr);
			}
		}
		pid_names = NULL;
		pid_starts = NULL;
		pid_ends = NULL;
	}
}