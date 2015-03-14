////////////////////////////////////////////////////////////////////////////////
// ExScene.h
// Author     : Bastien Bourineau
// Start Date : Junary 11th, 2012
// Copyright  : Copyright (c) 2011 OpenSpace3D
////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************
*                                                                                *
*   This program is free software; you can redistribute it and/or modify         *
*   it under the terms of the GNU Lesser General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or            *
*   (at your option) any later version.                                          *
*                                                                                *
**********************************************************************************/
#ifndef _EXSCENE_H
#define _EXSCENE_H


#include "ExOgreConverter.h"
#include "tinyxml2.h"


namespace EasyOgreExporter
{
	enum ExOgreLightType
	{
		OGRE_LIGHT_POINT,
		OGRE_LIGHT_DIRECTIONAL,
		OGRE_LIGHT_SPOT,
		OGRE_LIGHT_RADPOINT
	};
	
	typedef struct ExOgrePoint3Tag
	{
		float x, y, z;
		ExOgrePoint3Tag()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		ExOgrePoint3Tag(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
	} EasyOgrePoint3;

	typedef struct ExOgrePoint4Tag
	{
		float w, x, y, z;
		ExOgrePoint4Tag()
		{
			w = 0.0f;
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		ExOgrePoint4Tag(float W, float X, float Y, float Z)
		{
			w = W;
			x = X;
			y = Y;
			z = Z;
		}
	} EasyOgrePoint4;


  class ExScene
	{
	  public:
		  //constructor
		  ExScene(ExOgreConverter* converter);

		  //destructor
		  ~ExScene();

		  tinyxml2::XmlElement* writeNodeData(tinyxml2::XmlElement* parent, IGameNode* pGameNode, IGameObject::ObjectTypes type);
		  tinyxml2::XmlElement* writeEntityData(tinyxml2::XmlElement* parent, IGameNode* pGameNode, IGameMesh* pGameMesh, std::vector<ExMaterial*> lmat);
		  tinyxml2::XmlElement* writeCameraData(tinyxml2::XmlElement* parent, IGameCamera* pGameCamera);
		  tinyxml2::XmlElement* writeLightData(tinyxml2::XmlElement* parent, IGameLight* pGameLight);
      
   	  bool writeSceneFile();
	  protected:
		  int id_counter;
      ExOgreConverter* m_converter;
      std::string scenePath;
	  tinyxml2::XmlDocument* xmlDoc;
	  tinyxml2::XmlElement *sceneElement;
	  tinyxml2::XmlElement *nodesElement;
      
      void initXmlDocument();

		  std::string getLightTypeString(ExOgreLightType type);
      std::string getBoolString(bool value);
	  bool exportNodeAnimation(tinyxml2::XmlElement* pAnimsElement, IGameNode* pGameNode, Interval animRange, std::string name, bool resample, IGameObject::ObjectTypes type);
	};

}; // end of namespace

#endif
