#include "SkeletonAnimationModify.h"
#include "UtilWrap.h"

namespace EasyOgreExporter
{
	DEFINE_SET_GET_RETPFUNC(SkeletonAnimationModify, std::vector<Modify_ClipFrameItem>, clipFrameItemVec);

	SkeletonAnimationModify::SkeletonAnimationModify(IGameModifier* pGameModifier)
	{
		m_pGameModifie = pGameModifier;
		initModifyData();
	}

	SkeletonAnimationModify::~SkeletonAnimationModify()
	{

	}

	void SkeletonAnimationModify::initModifyData()
	{
		int numBlockparams;
		IPropertyContainer* pIPropertyContainer;
		IGameProperty* pBeginIGameProperty;
		IGameProperty* pEndIGameProperty;
		IParamBlock2* pBeginIParamBlock2;
		IParamBlock2* pEndIParamBlock2;

		pIPropertyContainer = m_pGameModifie->GetIPropertyContainer();
		pIPropertyContainer->GetNumberOfProperties();
		pIPropertyContainer->GetProperty(0);

		MCHAR* paramName;
		paramName = UtilWrap::A2W("afframes");
		pBeginIGameProperty = pIPropertyContainer->QueryProperty(paramName);
		pBeginIGameProperty->GetName();
		if (pBeginIGameProperty->IsPBlock2())
		{
			pBeginIParamBlock2 = pBeginIGameProperty->GetMaxParamBlock2();
			int numBlockparams = pBeginIParamBlock2->NumParams();
			int p = 0;
			ParamID pid_names = NULL;
			ParamID pid_starts = NULL;
			ParamID pid_ends = NULL;

			for (p = 0; p < numBlockparams; p++)
			{
				ParamID pid = pBeginIParamBlock2->IndextoID(p);
				ParamDef def = pBeginIParamBlock2->GetParamDef(pid);
				char * paramName = UtilWrap::W2A(def.int_name);
				if (UtilWrap::isStrEqual(paramName, "saveAnimClipNames")){
					pid_names = pid;
					if (pBeginIGameProperty->Count(pid)<minCount){ minCount = pBeginIGameProperty->Count(pid); }
				}
				if (UtilWrap::isStrEqual(paramName, "saveStartFrames")){
					pid_starts = pid;
					if (pBeginIGameProperty->Count(pid)<minCount){ minCount = pBeginIGameProperty->Count(pid); }
				}
				if (UtilWrap::isStrEqual(paramName, "saveEndFrames")){
					pid_ends = pid;
					if (pBeginIGameProperty->Count(pid)<minCount){ minCount = pBeginIGameProperty->Count(pid); }
				}
			}
		}

		paramName = UtilWrap::A2W("alframes");
		pEndIGameProperty = pIPropertyContainer->QueryProperty(paramName);
	}
}