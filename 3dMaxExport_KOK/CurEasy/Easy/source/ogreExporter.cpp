#include "OgreExporter.h"
#include "ExData.h"
#include "EasyOgreExporterLog.h"
#include "ExTools.h"
#include "tinyxml2.h"
#include "UtilWrap.h"

#include "../resources/resource.h"
#include "3dsmaxport.h"

#if defined(WIN32)
// For SHGetFolderPath.  Requires Windows XP or greater.
#include <stdarg.h>
#include <Shlobj.h>
#include <direct.h>
#endif // defined(WIN32)

#include "ExportDialog.h"
#include "KokConvert.h"

namespace EasyOgreExporter
{
	OgreSceneExporter::OgreSceneExporter()
	{
	}

	OgreSceneExporter::~OgreSceneExporter()
	{
	}

	int OgreSceneExporter::ExtCount(void)
	{
		return 1;
	}

	const TCHAR* OgreSceneExporter::Ext(int n)
	{
		return _T("scene");
	}

	const TCHAR* OgreSceneExporter::LongDesc(void)
	{
		return _T("Easy Ogre Exporter");
	}

	const TCHAR* OgreSceneExporter::ShortDesc(void)
	{
		return _T("Ogre Scene");
	}

	const TCHAR* OgreSceneExporter::AuthorName(void)
	{
		return _T("Bastien Bourineau for OpenSpace3D, based on Francesco Giordana and OC3 Entertainment, Inc. work");
	}

	const TCHAR* OgreSceneExporter::CopyrightMessage(void)
	{
		return _T("Copyright (c) 2011 OpenSpace3D");
	}

	const TCHAR* OgreSceneExporter::OtherMessage1(void)
	{
		return _T("");
	}

	const TCHAR* OgreSceneExporter::OtherMessage2(void)
	{
		return _T("");
	}

	unsigned int OgreSceneExporter::Version(void)
	{
		// Return Version number * 100.  100 = 1.00.
		return 100;
	}

	void OgreSceneExporter::ShowAbout(HWND hWnd)
	{
		//@todo
	}

	BOOL OgreSceneExporter::SupportsOptions(int ext, DWORD options)
	{
		return TRUE;
	}

	int	OgreSceneExporter::DoExport(const TCHAR* name, ExpInterface* pExpInterface, Interface* pInterface, BOOL suppressPrompts, DWORD options)
	{
		ParamList params;
		params = ExData::maxInterface.m_params;

		params.exportAll = (options & SCENE_EXPORT_SELECTED) ? false : true;

		// Using only a scene filename, construct the other paths
#ifdef UNICODE
		std::wstring scenePath_w = name;
		std::string scenePath;
		scenePath.assign(scenePath_w.begin(), scenePath_w.end());
#else
		std::string scenePath = name;
#endif
		for (int i = 0; i<scenePath.length(); ++i)
		{
			scenePath[i] = tolower(scenePath[i]);
		}

		size_t sceneIndex = scenePath.rfind(".scene", scenePath.length() - 1);
		size_t folderIndexForward = scenePath.rfind("/", scenePath.length() - 1);
		size_t folderIndexBackward = scenePath.rfind("\\", scenePath.length() - 1);
		size_t folderIndex;
		if (folderIndexForward == std::string::npos)
		{
			folderIndex = folderIndexBackward;
		}
		else if (folderIndexBackward == std::string::npos)
		{
			folderIndex = folderIndexForward;
		}
		else
		{
			folderIndex = folderIndexBackward > folderIndexForward ? folderIndexBackward : folderIndexForward;
		}

		if (sceneIndex == std::string::npos || folderIndex == std::string::npos)
		{
			MessageBox(GetCOREInterface()->GetMAXHWnd(), _T("Invalid scene filename."), _T("Error"), MB_OK);
			return false;
		}

		std::string outDir = scenePath.substr(0, folderIndex);
		std::string texOutDir = "bitmap";
		std::string meshOutDir = "mesh";
		std::string matOutDir = "material";
		std::string progOutDir = "program";
		std::string partOutDir = "particle";
		std::string sceneFile = scenePath.substr(folderIndex + 1, (sceneIndex - (folderIndex + 1)));
		std::string resPrefix = sceneFile;

		// Setup the paramlist.
		params.outputDir = outDir.c_str();
		params.texOutputDir = texOutDir.c_str();
		params.meshOutputDir = meshOutDir.c_str();
		params.materialOutputDir = matOutDir.c_str();
		params.programOutputDir = progOutDir.c_str();
		params.resPrefix = resPrefix.c_str();
		params.sceneFilename = sceneFile.c_str();

		int unitType = 0;
		float unitScale = 0;
		GetMasterUnitInfo(&unitType, &unitScale);
		params.lum = ConvertToMeter(unitType) * unitScale;

#ifdef UNICODE
		std::wstring plugConfDir_w = IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR);
		std::string plugConfDir;
		plugConfDir.assign(plugConfDir_w.begin(), plugConfDir_w.end());
#else
		std::string plugConfDir = IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR);
#endif
		std::string xmlConfPath = plugConfDir + "\\EasyOgreExporter\\config.xml";
		loadExportConf(xmlConfPath, params);

		ExData::maxInterface.m_params = params;

		if (!DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_PANEL), pInterface->GetMAXHWnd(), IGameExporterOptionsDlgProc, (LPARAM)&(ExData::maxInterface.m_params)))
		{
			return 1;
		}

		return ExData::maxInterface.exportScene();
	}

	void OgreSceneExporter::loadExportConf(std::string path, ParamList &param)
	{
		tinyxml2::XMLDocument xmlDoc;
		if (UtilWrap::isTinyXmlSuccess(xmlDoc.LoadFile(path.c_str())))
		{
			tinyxml2::XMLElement* rootElem = xmlDoc.RootElement();
			tinyxml2::XMLElement* child = rootElem->FirstChildElement("IDC_OGREVERSION");
			if (child)
			{
				if (child->GetText())
				{
					switch (atoi(child->GetText()))
					{
					case 0:
						param.meshVersion = TOGRE_LASTEST;
						break;
					case 1:
						param.meshVersion = TOGRE_1_8;
						break;
					case 2:
						param.meshVersion = TOGRE_1_7;
						break;
					case 3:
						param.meshVersion = TOGRE_1_4;
						break;
					case 4:
						param.meshVersion = TOGRE_1_0;
						break;
					}
				}
			}

			child = rootElem->FirstChildElement("IDC_RESPREFIX");
			if (child)
				param.resPrefix = child->GetText() ? child->GetText() : "";

			child = rootElem->FirstChildElement("IDC_MATDIR");
			if (child)
				param.materialOutputDir = child->GetText() ? child->GetText() : "";

			child = rootElem->FirstChildElement("IDC_TEXDIR");
			if (child)
				param.texOutputDir = child->GetText() ? child->GetText() : "";

			child = rootElem->FirstChildElement("IDC_MESHDIR");
			if (child)
				param.meshOutputDir = child->GetText() ? child->GetText() : "";

			child = rootElem->FirstChildElement("IDC_PROGDIR");
			if (child)
				param.programOutputDir = child->GetText() ? child->GetText() : "";

			child = rootElem->FirstChildElement("IDC_YUPAXIS");
			if (child)
				param.yUpAxis = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_SHAREDGEOM");
			if (child)
				param.useSharedGeom = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_GENLOD");
			if (child)
				param.generateLOD = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_EDGELIST");
			if (child)
				param.buildEdges = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_TANGENT");
			if (child)
				param.buildTangents = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_SPLITMIRROR");
			if (child)
				param.tangentsSplitMirrored = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_SPLITROT");
			if (child)
				param.tangentsSplitRotated = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_STOREPARITY");
			if (child)
				param.tangentsUseParity = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_CONVDDS");
			if (child)
				param.convertToDDS = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_RESAMPLE_ANIMS");
			if (child)
				param.resampleAnims = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_RESAMPLE_STEP");
			if (child)
				param.resampleStep = (child->GetText()) ? atoi(child->GetText()) : 1;

			child = rootElem->FirstChildElement("IDC_LOGS");
			if (child)
				param.enableLogs = (child->GetText() && (atoi(child->GetText()) == 1)) ? true : false;

			child = rootElem->FirstChildElement("IDC_SHADERMODE");
			if (child)
			{
				if (child->GetText())
				{
					switch (atoi(child->GetText()))
					{
					case 0:
						param.exportProgram = SHADER_NONE;
						break;
					case 1:
						param.exportProgram = SHADER_BUMP;
						break;
					case 2:
						param.exportProgram = SHADER_ALL;
						break;
					case 3:
						param.exportProgram = SHADER_ALL_MULTI;
						break;
					}
				}
			}

			child = rootElem->FirstChildElement("IDC_TEXSIZE");
			if (child && child->GetText())
				param.maxTextureSize = atoi(child->GetText());

			child = rootElem->FirstChildElement("IDC_NUMMIPS");
			if (child && child->GetText())
				param.maxMipmaps = atoi(child->GetText());
		}
	}

	// Dummy function for progress bar.
	DWORD WINAPI fn(LPVOID arg)
	{
		return 0;
	}

	OgreExporter::OgreExporter() :
		pIGame(NULL),
		sceneData(0),
		ogreConverter(0),
		nodeCount(0)
	{
	}

	OgreExporter::~OgreExporter()
	{
	}

	void OgreExporter::saveExportConf(std::string path)
	{
		tinyxml2::XMLDocument xmlDoc;
		tinyxml2::XMLElement* contProperties = xmlDoc.NewElement("Config");
		xmlDoc.LinkEndChild(contProperties);

		std::stringstream oVersionVal;
		oVersionVal << m_params.meshVersion;
		tinyxml2::XMLElement* child = xmlDoc.NewElement("IDC_OGREVERSION");
		tinyxml2::XMLText* childText = xmlDoc.NewText(oVersionVal.str().c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_RESPREFIX");
		childText = xmlDoc.NewText(m_params.resPrefix.c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_MATDIR");
		childText = xmlDoc.NewText(m_params.materialOutputDir.c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_TEXDIR");
		childText = xmlDoc.NewText(m_params.texOutputDir.c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_MESHDIR");
		childText = xmlDoc.NewText(m_params.meshOutputDir.c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_PROGDIR");
		childText = xmlDoc.NewText(m_params.programOutputDir.c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_YUPAXIS");
		childText = xmlDoc.NewText(m_params.yUpAxis ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_SHAREDGEOM");
		childText = xmlDoc.NewText(m_params.useSharedGeom ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_GENLOD");
		childText = xmlDoc.NewText(m_params.generateLOD ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_EDGELIST");
		childText = xmlDoc.NewText(m_params.buildEdges ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_TANGENT");
		childText = xmlDoc.NewText(m_params.buildTangents ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_SPLITMIRROR");
		childText = xmlDoc.NewText(m_params.tangentsSplitMirrored ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_SPLITROT");
		childText = xmlDoc.NewText(m_params.tangentsSplitRotated ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_STOREPARITY");
		childText = xmlDoc.NewText(m_params.tangentsUseParity ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_RESAMPLE_ANIMS");
		childText = xmlDoc.NewText(m_params.resampleAnims ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_RESAMPLE_STEP");
		char tmpbuf[10] = { 0 };
		sprintf(tmpbuf, "%d", m_params.resampleStep);
		childText = xmlDoc.NewText(tmpbuf);
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_LOGS");
		childText = xmlDoc.NewText(m_params.enableLogs ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		child = xmlDoc.NewElement("IDC_CONVDDS");
		childText = xmlDoc.NewText(m_params.convertToDDS ? "1" : "0");
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		std::stringstream oShaderVal;
		oShaderVal << m_params.exportProgram;
		child = xmlDoc.NewElement("IDC_SHADERMODE");
		childText = xmlDoc.NewText(oShaderVal.str().c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		std::stringstream oTexVal;
		oTexVal << m_params.maxTextureSize;
		child = xmlDoc.NewElement("IDC_TEXSIZE");
		childText = xmlDoc.NewText(oTexVal.str().c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		std::stringstream oMipsVal;
		oMipsVal << m_params.maxMipmaps;
		child = xmlDoc.NewElement("IDC_NUMMIPS");
		childText = xmlDoc.NewText(oMipsVal.str().c_str());
		child->LinkEndChild(childText);
		contProperties->LinkEndChild(child);

		xmlDoc.SaveFile(path.c_str());
	}

	void OgreExporter::initIGameConf(std::string path)
	{
		tinyxml2::XMLDocument xmlDoc;
		tinyxml2::XMLElement* igameProperties = xmlDoc.NewElement("IGameProperties");
		xmlDoc.LinkEndChild(igameProperties);
		tinyxml2::XMLElement* igameUserData = xmlDoc.NewElement("ExportUserData");
		igameProperties->LinkEndChild(igameUserData);

		// renderingDistance
		tinyxml2::XMLElement* renderDist = xmlDoc.NewElement("UserProperty");
		tinyxml2::XMLElement* renderDistId = xmlDoc.NewElement("id");
		tinyxml2::XMLText* renderDistIdText = xmlDoc.NewText("102");
		renderDistId->LinkEndChild(renderDistIdText);
		renderDist->LinkEndChild(renderDistId);

		tinyxml2::XMLElement* renderDistSName = xmlDoc.NewElement("simplename");
		tinyxml2::XMLText* renderDistSNameText = xmlDoc.NewText("renderingDistance");
		renderDistSName->LinkEndChild(renderDistSNameText);
		renderDist->LinkEndChild(renderDistSName);

		tinyxml2::XMLElement* renderDistName = xmlDoc.NewElement("keyName");
		tinyxml2::XMLText* renderDistNameText = xmlDoc.NewText("renderingDistance");
		renderDistName->LinkEndChild(renderDistNameText);
		renderDist->LinkEndChild(renderDistName);

		tinyxml2::XMLElement* renderDistType = xmlDoc.NewElement("type");
		tinyxml2::XMLText* renderDistTypeText = xmlDoc.NewText("float");
		renderDistType->LinkEndChild(renderDistTypeText);
		renderDist->LinkEndChild(renderDistType);

		igameUserData->LinkEndChild(renderDist);

		// noLOD
		tinyxml2::XMLElement* noLod = xmlDoc.NewElement("UserProperty");
		tinyxml2::XMLElement* noLodId = xmlDoc.NewElement("id");
		tinyxml2::XMLText* noLodIdText = xmlDoc.NewText("103");
		noLodId->LinkEndChild(noLodIdText);
		noLod->LinkEndChild(noLodId);

		tinyxml2::XMLElement* noLodSName = xmlDoc.NewElement("simplename");
		tinyxml2::XMLText* noLodSNameText = xmlDoc.NewText("noLOD");
		noLodSName->LinkEndChild(noLodSNameText);
		noLod->LinkEndChild(noLodSName);

		tinyxml2::XMLElement* noLodName = xmlDoc.NewElement("keyName");
		tinyxml2::XMLText* noLodNameText = xmlDoc.NewText("noLOD");
		noLodName->LinkEndChild(noLodNameText);
		noLod->LinkEndChild(noLodName);

		tinyxml2::XMLElement* noLodType = xmlDoc.NewElement("type");
		tinyxml2::XMLText* noLodTypeText = xmlDoc.NewText("bool");
		noLodType->LinkEndChild(noLodTypeText);
		noLod->LinkEndChild(noLodType);

		igameUserData->LinkEndChild(noLod);

		// userData
		tinyxml2::XMLElement* userData = xmlDoc.NewElement("UserProperty");
		tinyxml2::XMLElement* userDataId = xmlDoc.NewElement("id");
		tinyxml2::XMLText* userDataIdText = xmlDoc.NewText("104");
		userDataId->LinkEndChild(userDataIdText);
		userData->LinkEndChild(userDataId);

		tinyxml2::XMLElement* userDataSName = xmlDoc.NewElement("simplename");
		tinyxml2::XMLText* userDataSNameText = xmlDoc.NewText("userData");
		userDataSName->LinkEndChild(userDataSNameText);
		userData->LinkEndChild(userDataSName);

		tinyxml2::XMLElement* userDataName = xmlDoc.NewElement("keyName");
		tinyxml2::XMLText* userDataNameText = xmlDoc.NewText("userData");
		userDataName->LinkEndChild(userDataNameText);
		userData->LinkEndChild(userDataName);

		tinyxml2::XMLElement* userDataType = xmlDoc.NewElement("type");
		tinyxml2::XMLText* userDataTypeText = xmlDoc.NewText("string");
		userDataType->LinkEndChild(userDataTypeText);
		userData->LinkEndChild(userDataType);

		igameUserData->LinkEndChild(userData);

		xmlDoc.SaveFile(path.c_str());
	}

	bool OgreExporter::exportScene()
	{
		nodeCount = 0;

		//Init log files
		std::string logFileName = "";
		if (m_params.enableLogs)
		{
			logFileName = m_params.outputDir;
			logFileName.append("\\easyOgreExporter.log");
			EasyOgreExporter::EasyOgreExporterLogFile::SetPath(logFileName.data());
		}
		else
		{
			EasyOgreExporter::EasyOgreExporterLogFile::SetPath(logFileName.data());
		}


#if defined(WIN32)
		if (m_params.exportMaterial)
			_mkdir((makeOutputPath(m_params.outputDir, m_params.materialOutputDir, "", "")).c_str());

		if (m_params.exportProgram != SHADER_NONE)
			_mkdir((makeOutputPath(m_params.outputDir, m_params.programOutputDir, "", "")).c_str());

		if (m_params.copyTextures)
			_mkdir((makeOutputPath(m_params.outputDir, m_params.texOutputDir, "", "")).c_str());

		_mkdir((makeOutputPath(m_params.outputDir, m_params.meshOutputDir, "", "")).c_str());
#endif

		// Create Ogre Root
		// Ogre::Root ogreRoot;
		// Create singletons
		//Ogre::LogManager logMgr;
		//Ogre::LogManager::getSingleton().createLog("Ogre.log", true);
		//Ogre::ResourceGroupManager rgm;
		//Ogre::MeshManager meshMgr;
		//Ogre::SkeletonManager skelMgr;
		//Ogre::MaterialManager matMgr;
		//Ogre::DefaultHardwareBufferManager hardwareBufMgr;
		//Ogre::LodStrategyManager lodstrategymanager;  

		m_params.currentRootJoints.clear();

#ifdef UNICODE
		std::wstring plugConfDir_w = IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR);
		std::string plugConfDir;
		plugConfDir.assign(plugConfDir_w.begin(), plugConfDir_w.end());
#else
		std::string plugConfDir = IPathConfigMgr::GetPathConfigMgr()->GetDir(APP_PLUGCFG_DIR);
#endif

		_mkdir((std::string(plugConfDir + "\\EasyOgreExporter")).c_str());

		std::string xmlIGameConfPath = plugConfDir + "\\EasyOgreExporter\\IGameProp.xml";
		initIGameConf(xmlIGameConfPath);

		std::string xmlConfPath = plugConfDir + "\\EasyOgreExporter\\config.xml";
		saveExportConf(xmlConfPath);

		pIGame = GetIGameInterface();
#ifdef UNICODE
		std::wstring xmlIGameConfPath_w;
		xmlIGameConfPath_w.assign(xmlIGameConfPath.begin(), xmlIGameConfPath.end());
		pIGame->SetPropertyFile(xmlIGameConfPath_w.data());
#else
		pIGame->SetPropertyFile(xmlIGameConfPath.c_str());
#endif

		// Passing in true causing crash on IGameNode->GetNodeParent.  
		// Test for selection in Translate node.
		pIGame->InitialiseIGame(false);
		pIGame->SetStaticFrame(0);

		std::string sTitle = "Easy Ogre Exporter: " + m_params.sceneFilename;
#ifdef UNICODE
		std::wstring title_w;
		title_w.assign(sTitle.begin(), sTitle.end());
		GetCOREInterface()->ProgressStart(title_w.data(), TRUE, progressCb, 0);
#else
		GetCOREInterface()->ProgressStart((char*)sTitle.c_str(), TRUE, progressCb, 0);
#endif

		//WARNING this apply transform only matrix from on iGameNode not on max iNode
		IGameConversionManager* pConversionManager = GetConversionManager();
		if(m_params.yUpAxis)
		{
			pConversionManager->SetCoordSystem(IGameConversionManager::IGAME_OGL);
		}
		else
		{
			pConversionManager->SetCoordSystem(IGameConversionManager::IGAME_MAX);
		}

		Interval animInterval = GetCOREInterface()->GetAnimRange();

		// 导出流程
		//ogreConverter = new ExOgreConverter(pIGame, m_params);
		ogreConverter = (ExOgreConverter*)(new KokConvert(pIGame, m_params));

		//Init Scene
		if(m_params.exportScene)
			sceneData = new ExScene(ogreConverter);

		// parse Max scene to find bones used in skins
		for (int node = 0; node < pIGame->GetTopLevelNodeCount(); ++node)
		{
			IGameNode* pGameNode = pIGame->GetTopLevelNode(node);
			if (pGameNode)
			{
				LoadSkinBones(pGameNode);
			}
		}

		// parse Max scene
		for (int node = 0; node < pIGame->GetTopLevelNodeCount(); ++node)
		{
			IGameNode* pGameNode = pIGame->GetTopLevelNode(node);
			if (pGameNode)
			{
				exportNode(pGameNode, 0);
			}
		}

		if (sceneData)
		{
#ifdef UNICODE
			GetCOREInterface()->ProgressUpdate(95, FALSE, L"Writing scene file.");
#else
			GetCOREInterface()->ProgressUpdate(95, FALSE, "Writing scene file.");
#endif
			sceneData->writeSceneFile();
		}

		if (ogreConverter)
		{
#ifdef UNICODE
			GetCOREInterface()->ProgressUpdate(98, FALSE, L"Writing material file.");
#else
			GetCOREInterface()->ProgressUpdate(98, FALSE, "Writing material file.");
#endif
			ogreConverter->writeMaterialFile();
		}

		if (sceneData)
		{
			delete sceneData;
			sceneData = 0;
		}

		if (ogreConverter)
		{
			delete ogreConverter;
			ogreConverter = 0;
		}

		pIGame->ReleaseIGame();

#ifdef UNICODE
		GetCOREInterface()->ProgressUpdate(99, FALSE, L"Done.");
#else
		GetCOREInterface()->ProgressUpdate(99, FALSE, "Done.");
#endif
		EasyOgreExporterLog("Info: export done.\n");

		//close the progress bar
		GetCOREInterface()->ProgressEnd();
		lFoundBones.clear();

		MessageBox(GetCOREInterface()->GetMAXHWnd(), _T("Export done successfully."), _T("Info"), MB_OK);
		return true;
	}

	void OgreExporter::LoadSkinBones(IGameNode* pGameNode)
	{
		IGameObject* pGameObject = pGameNode->GetIGameObject();
		if (pGameObject)
		{
			IGameObject::ObjectTypes gameType = pGameObject->GetIGameType();

			if (gameType == IGameObject::IGAME_MESH)
			{
				IGameMesh* pGameMesh = static_cast<IGameMesh*>(pGameObject);
				if (pGameMesh)
				{
					//search skin modifier
					int numModifiers = pGameMesh->GetNumModifiers();
					for (int i = 0; i < numModifiers; ++i)
					{
						IGameModifier* pGameModifier = pGameMesh->GetIGameModifier(i);
						if (pGameModifier)
						{
							if (pGameModifier->IsSkin())
							{
								IGameSkin* pGameSkin = static_cast<IGameSkin*>(pGameModifier);
								for (int j = 0; j < pGameSkin->GetTotalBoneCount(); ++j)
								{
									INode* bone = pGameSkin->GetBone(j, true);
									lFoundBones.push_back(bone);
								}

								ogreConverter->addSkinModifier(pGameSkin);
							}
						}
					}
				}
			}

			pGameNode->ReleaseIGameObject();
		}

		for (int i = 0; i < pGameNode->GetChildCount(); ++i)
		{
			IGameNode* pChildGameNode = pGameNode->GetNodeChild(i);
			if (pChildGameNode)
			{
				LoadSkinBones(pChildGameNode);
			}
		}
	}

	bool OgreExporter::IsSkinnedBone(IGameNode* pGameNode)
	{
		INode* node = pGameNode->GetMaxNode();
		for (unsigned int i = 0; i < lFoundBones.size(); i++)
		{
			if (lFoundBones[i] == node)
				return true;
		}

		return false;
	}

	bool OgreExporter::IsNodeToExport(IGameNode* pGameNode)
	{
		bool bShouldExport = false;

		if (pGameNode)
		{
			IGameObject* pGameObject = pGameNode->GetIGameObject();
			if (pGameObject)
			{
				IGameObject::ObjectTypes gameType = pGameObject->GetIGameType();
				IGameObject::MaxType maxType = pGameObject->GetMaxType();
				INode* node = pGameNode->GetMaxNode();
				if (node)
				{
					ILayer* layer = (ILayer*)node->GetReference(NODE_LAYER_REF);

					if (node->IsObjectHidden() || layer->IsHidden()
						// Only export selection if exportAll = false
						|| (node->Selected() == 0 && !m_params.exportAll)
						// Do not export bones
						|| node->GetBoneNodeOnOff() || IsSkinnedBone(pGameNode)
						|| (maxType == IGameObject::IGAME_MAX_UNKNOWN || maxType == IGameObject::IGAME_MAX_BONE ||
						gameType == IGameObject::IGAME_BONE || gameType == IGameObject::IGAME_IKCHAIN ||
						gameType == IGameObject::IGAME_UNKNOWN))
					{
						bShouldExport = false;
					}
					else
					{
						bShouldExport = true;
					}
				}
				pGameNode->ReleaseIGameObject();
			}
		}
		return bShouldExport;
	}

	bool OgreExporter::exportNode(IGameNode* pGameNode, tinyxml2::XMLElement* parent)
	{
		GetCOREInterface()->ProgressUpdate((int)(((float)nodeCount / (float)pIGame->GetTotalNodeCount()) * 90.0f), TRUE);

		if (IsNodeToExport(pGameNode))
		{
			GetCOREInterface()->ProgressUpdate((int)(((float)nodeCount / (float)pIGame->GetTotalNodeCount()) * 90.0f), FALSE, pGameNode->GetName());

#ifdef UNICODE
			MSTR nodeName = pGameNode->GetName();
			EasyOgreExporterLog("Found node: %ls\n", nodeName.data());
#else
			EasyOgreExporterLog("Found node: %s\n", pGameNode->GetName());
#endif

			IGameObject* pGameObject = pGameNode->GetIGameObject();
			if (pGameObject)
			{
				IGameObject::ObjectTypes gameType = pGameObject->GetIGameType();

				switch (gameType)
				{
				case IGameObject::IGAME_MESH:
				{
					bool delTri = false;
					Mesh* mMesh = 0;
					INode* node = pGameNode->GetMaxNode();
					TriObject* triObj = getTriObjectFromNode(node, GetFirstFrame(), delTri);

					if (triObj)
						mMesh = &triObj->GetMesh();

					int numFaces = 0;
					if(mMesh)
					{
						numFaces = mMesh->getNumFaces();

						//free the tree object
						if (delTri && triObj)
						{
							triObj->DeleteThis();
							triObj = 0;
							delTri = false;
						}
					}

					IGameMesh* pGameMesh = static_cast<IGameMesh*>(pGameObject);
					if (pGameMesh && (numFaces > 0))
					{
						if (pGameMesh->InitializeData())
						{
#ifdef UNICODE
							MSTR nodeName = pGameNode->GetName();
							EasyOgreExporterLog("Found mesh node: %ls\n", nodeName.data());
#else
							EasyOgreExporterLog("Found mesh node: %s\n", pGameNode->GetName());
#endif

							std::vector<ExMaterial*> lmat;
							if (ogreConverter)
							{
								if (!ogreConverter->writeEntityData(pGameNode, pGameObject, pGameMesh, lmat))
								{
									EasyOgreExporterLog("Warning, mesh skipped\n");
								}
								else if (sceneData)
								{
									parent = sceneData->writeNodeData(parent, pGameNode, IGameObject::IGAME_MESH);
									sceneData->writeEntityData(parent, pGameNode, pGameMesh, lmat);
								}
							}
						}
					}
					else
					{
#ifdef UNICODE
						MSTR nodeName = pGameNode->GetName();
						EasyOgreExporterLog("Warning, Mesh : %ls skipped, no faces found\n", nodeName.data());
#else
						EasyOgreExporterLog("Warning, Mesh node: %s skipped, no faces found\n", pGameNode->GetName());
#endif
					}
				}
				break;
				case IGameObject::IGAME_LIGHT:
				{
					if (m_params.exportLights)
					{
						IGameLight* pGameLight = static_cast<IGameLight*>(pGameObject);
						if (pGameLight)
						{
#ifdef UNICODE
							MSTR nodeName = pGameNode->GetName();
							EasyOgreExporterLog("Found light: %ls\n", nodeName.data());
#else
							EasyOgreExporterLog("Found light: %s\n", pGameNode->GetName());
#endif
							if (sceneData)
							{
								parent = sceneData->writeNodeData(parent, pGameNode, IGameObject::IGAME_LIGHT);
								sceneData->writeLightData(parent, pGameLight);
							}
						}
					}
				}
				break;
				case IGameObject::IGAME_CAMERA:
				{
					if (m_params.exportCameras)
					{
						IGameCamera* pGameCamera = static_cast<IGameCamera*>(pGameObject);
						if (pGameCamera)
						{
#ifdef UNICODE
							MSTR nodeName = pGameNode->GetName();
							EasyOgreExporterLog("Found camera: %ls\n", nodeName.data());
#else
							EasyOgreExporterLog("Found camera: %s\n", pGameNode->GetName());
#endif

							if (sceneData)
							{
								parent = sceneData->writeNodeData(parent, pGameNode, IGameObject::IGAME_CAMERA);
								sceneData->writeCameraData(parent, pGameCamera);
							}
						}
					}
				}
				break;
				case IGameObject::IGAME_HELPER:
				{
					parent = sceneData->writeNodeData(parent, pGameNode, IGameObject::IGAME_HELPER);
				}
				break;
				default:
					break;
				}
			}
		}

		if (pGameNode)
		{
			for (int i = 0; i < pGameNode->GetChildCount(); ++i)
			{
				IGameNode* pChildGameNode = pGameNode->GetNodeChild(i);
				if (pChildGameNode)
				{
					exportNode(pChildGameNode, parent);
				}
			}
		}

		pGameNode->ReleaseIGameObject();

		nodeCount++;

		return true;
	}
} // end namespace


class EasyOgreExporterClassDesc :public ClassDesc2
{
public:
	int 			IsPublic() { return TRUE; }
	void *			Create(BOOL loading = FALSE) { return new EasyOgreExporter::OgreSceneExporter(); }
	const TCHAR *	ClassName() { return _T("OgreExporter"); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	Class_ID		ClassID() { return Class_ID(0x6a042a9d, 0x75b54fc4); }
	const TCHAR* 	Category() { return _T("OGRE"); }
	const TCHAR*	InternalName() { return _T("OgreExporter"); }
	HINSTANCE		HInstance() { return hInstance; }
};


static EasyOgreExporterClassDesc EasyOgreExporterDesc;
ClassDesc2* GetEasyOgreExporterDesc() { return &EasyOgreExporterDesc; }

