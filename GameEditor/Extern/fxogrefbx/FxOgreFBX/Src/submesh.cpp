////////////////////////////////////////////////////////////////////////////////
// submesh.cpp
// Author     : Francesco Giordana
// Start Date : January 13, 2005
// Copyright  : (C) 2006 by Francesco Giordana
// Email      : fra.giordana@tiscali.it
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Port to 3D Studio Max - Modified original version
// Author	  : Doug Perkowski - OC3 Entertainment, Inc.
// Start Date : December 10th, 2007
////////////////////////////////////////////////////////////////////////////////
// Port to FBX - Modified original version
// Author	  : Doug Perkowski - OC3 Entertainment, Inc.
// Start Date : January 8th, 2012
////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************
*                                                                                *
*   This program is free software; you can redistribute it and/or modify         *
*   it under the terms of the GNU Lesser General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or            *
*   (at your option) any later version.                                          *
*                                                                                *
**********************************************************************************/

#include "submesh.h"
#include "common.h"
namespace FxOgreFBX
{
    /***** Class Submesh *****/
    // constructor
    Submesh::Submesh(const std::string& name)
    {
        m_pBlendShape = NULL;
        clear();
        m_name = name;
    }

    // destructor
    Submesh::~Submesh()
    {
        clear();
    }

    // clear data
    void Submesh::clear()
    {
        m_name = "";
        m_numTriangles = 0;
        m_pMaterial = NULL;
        m_vertices.clear();
        m_faces.clear();
        m_uvsets.clear();
        m_use32bitIndexes = false;
        m_bbox.clear();
        // Doug Perkowski - Cleaning up BlendShapes in Mesh.cpp.
//		if (m_pBlendShape)
//			delete m_pBlendShape;
        m_pBlendShape = NULL;
    }

    // return number of triangles composing the mesh
    long Submesh::numTriangles()
    {
        return m_numTriangles;
    }

    // return number of vertices composing the mesh
    long Submesh::numVertices()
    {
        return m_numVertices;
    }

    // return submesh name
    std::string& Submesh::name()
    {
        return m_name;
    }

/***** load data *****/

    bool Submesh::loadMaterial(FbxSurfaceMaterial* pGameMaterial,std::vector<int>& uvsets,ParamList& params)
    {
        
        //check if this material has already been created
        //fix material name, adding the requested prefix
        std::string tmpStr = params.matPrefix;
        if(pGameMaterial)
            tmpStr.append(pGameMaterial->GetName());
        std::string name = "";
        for(size_t i = 0; i < tmpStr.size(); ++i)
        {
            if(tmpStr[i] == ':')
            {
                name.append("_");
            }
            else
            {
                name.append(tmpStr.substr(i, 1));
            }
        }
        Material* pMaterial = MaterialSet::getSingleton().getMaterial(name);
        //if the material has already been created, update the pointer
        if (pMaterial)
            m_pMaterial = pMaterial;
        //else create it and add it to the material set
        else
        {
            pMaterial = new Material();
            pMaterial->load(pGameMaterial,uvsets,params);
            m_pMaterial = pMaterial;
            MaterialSet::getSingleton().addMaterial(pMaterial);
        }
        //loading complete
        
        return true;
 
    }

    bool Submesh::load(FbxNode* pNode, FbxMesh* pMesh, const std::vector<face>& faces, const std::vector<vertexInfo>& vertInfo, const std::vector<FbxVector4>& points, 
        const std::vector<FbxVector4>& normals, const std::vector<int>& texcoordsets, ParamList& params, const FbxAMatrix& bindPose, bool opposite )
    {
        //save the mesh from which this submesh will be created
        m_pNode = pNode;

        size_t i,j,k;
        FxOgreFBXLog( "Loading submesh associated to material: %s ...\n", m_pMaterial->name().c_str());
        
        //save uvsets info
        for (i=m_uvsets.size(); i<texcoordsets.size(); i++)
        {
            uvset uv;
            uv.size = 2;
            m_uvsets.push_back(uv);
        }
        //iterate over faces array, to retrieve vertices info
        for (i=0; i<faces.size(); i++)
        {
            face newFace;
            // if we are using shared geometry, indexes refer to the vertex buffer of the whole mesh
            if (params.useSharedGeom)
            {
                if(opposite)
                {	// reverse order of face vertices for correct culling
                    newFace.v[0] = faces[i].v[2];
                    newFace.v[1] = faces[i].v[1];
                    newFace.v[2] = faces[i].v[0];
                }
                else
                {
                    newFace.v[0] = faces[i].v[0];
                    newFace.v[1] = faces[i].v[1];
                    newFace.v[2] = faces[i].v[2];
                }
            }
            // otherwise we create a vertex buffer for this submesh
            else
            {	// faces are triangles, so retrieve index of the three vertices
                for (j=0; j<3; j++)
                {
                    vertex v;
                    vertexInfo vInfo = vertInfo[faces[i].v[j]];
                    // save vertex coordinates (rescale to desired length unit)
                    assert(vInfo.pointIdx >= 0 && vInfo.pointIdx < static_cast<int>(points.size()));
                    FbxVector4 point = points[vInfo.pointIdx] * params.lum;
                    if (fabs(point[0]) < PRECISION)
                        point[0] = 0;
                    if (fabs(point[1]) < PRECISION)
                        point[1] = 0;
                    if (fabs(point[2]) < PRECISION)
                        point[2] = 0;
                    v.x = point[0];
                    v.y = point[1];
                    v.z = point[2];
					
                    m_bbox.merge(Point3(v.x, v.y, v.z));

                    // save vertex normal
                    assert(vInfo.normalIdx >= 0 && vInfo.normalIdx < static_cast<int>(normals.size()));
                    FbxVector4 normal = normals[vInfo.normalIdx];
                    if (fabs(normal[0]) < PRECISION)
                        normal[0] = 0;
                    if (fabs(normal[1]) < PRECISION)
                        normal[1] = 0;
                    if (fabs(normal[2]) < PRECISION)
                        normal[2] = 0;
                    v.n.x = normal[0];
                    v.n.y = normal[1];
                    v.n.z = normal[2];
                    if (opposite)
                    {
                        // Reversing the winding order appears to be sufficent.
                        v.n.x = -normal[0];
                        v.n.y = -normal[1];
                        v.n.z = -normal[2];
                    }
                    v.n.Normalize();

                    // save vertex color
                    v.r = vInfo.r;
                    v.g = vInfo.g;
                    v.b = vInfo.b;
                    v.a = vInfo.a;
                    // save vertex bone assignements
                    for (k=0; k<vInfo.vba.size(); k++)
                    {
                        vba newVba;
                        newVba.jointIdx = vInfo.jointIds[k];
                        newVba.weight = vInfo.vba[k];
                        v.vbas.push_back(newVba);
                    }
                    // save texture coordinates
                    for (k=0; k<vInfo.u.size(); k++)
                    {
                        texcoord newTexCoords;
                        newTexCoords.u = vInfo.u[k];
                        newTexCoords.v = vInfo.v[k];
                        newTexCoords.w = 0;
                        v.texcoords.push_back(newTexCoords);
                    }
                    // save vertex index in mesh, to retrieve future positions of the same vertex
                    v.index = vInfo.pointIdx;
                    // add newly created vertex to vertex list
                    m_vertices.push_back(v);
                    if (opposite)	// reverse order of face vertices to get correct culling
                        newFace.v[2-j] = static_cast<int>(m_vertices.size()) - 1;
                    else
                        newFace.v[j] = static_cast<int>(m_vertices.size()) - 1;
                }
            }
            m_faces.push_back(newFace);
        }
        // set use32bitIndexes flag
        if (params.useSharedGeom || (m_vertices.size() > 65535) || (m_faces.size() > 65535))
            m_use32bitIndexes = true;
        else
            m_use32bitIndexes = false;

        // add submesh pointer to m_params list
        params.loadedSubmeshes.push_back(this);

        FxOgreFBXLog( "DONE\n");
        
        return true;
    }
    
    // Load a keyframe for this submesh
    bool Submesh::loadKeyframe(Track& t,float time,ParamList& params)
    {
        // create a new keyframe
        vertexKeyframe k;
        // set keyframe time
        k.time = time;

        bool bIsObjectSpace = true;
        if (params.exportWorldCoords)
            bIsObjectSpace = false;
/*
        IGameMesh* pGameMesh = (IGameMesh*)m_pNode->GetIGameObject();
        if(!pGameMesh)
            return false;
        if(!pGameMesh->InitializeData() )
            return false;
        assert(pGameMesh->GetNumberOfVerts()==m_vertices.size());
        // calculate vertex offsets
        for (int i=0; i<m_vertices.size(); i++)
        {
            vertexPosition pos;
            vertex v = m_vertices[i];
            assert(pGameMesh->GetNumberOfVerts() > v.index);
            Point3 point = pGameMesh->GetVertex(v.index, bIsObjectSpace);
            pos.x = point.x;
            pos.y = point.y;
            pos.z = point.z;
            if (fabs(pos.x) < PRECISION)
                    pos.x = 0;
            if (fabs(pos.y) < PRECISION)
                pos.y = 0;
            if (fabs(pos.z) < PRECISION)
                pos.z = 0;
            k.positions.push_back(pos);
        }
        // add keyframe to given track
        t.addVertexKeyframe(k);
        if (params.vertBB)
        {
            Box3 bbox;
            pGameMesh->GetBoundingBox(bbox);
            if (params.exportWorldCoords)
                bbox = bbox * m_pNode->GetWorldTM(GetCOREInterface()->GetTime()).ExtractMatrix3();
            m_boundingBox += bbox;
        }
        m_pNode->ReleaseIGameObject();
*/
        // keyframe successfully loaded
        return true;
    }



/***** Export data *****/
    // Write submesh data to an Ogre compatible mesh
#if OGRE_VERSION < 0x020000
    bool Submesh::createOgreSubmesh(Ogre::MeshPtr pMesh,const ParamList& params)
#else
	bool Submesh::createOgreSubmesh(Ogre::v1::MeshPtr pMesh, const ParamList& params)
#endif
    {
        size_t i,j;
        bool stat;
        // Create a new submesh
#if OGRE_VERSION < 0x020000
        Ogre::SubMesh* pSubmesh;
#else
		Ogre::v1::SubMesh* pSubmesh;
#endif
        if (m_name != "")
            pSubmesh = pMesh->createSubMesh(m_name.c_str());
        else
            pSubmesh = pMesh->createSubMesh();
        // Set material
        pSubmesh->setMaterialName(m_pMaterial->name().c_str());
        // Set use shared geometry flag
        pSubmesh->useSharedVertices = params.useSharedGeom;
#if OGRE_VERSION < 0x020000
		// Create vertex data for current submesh
        pSubmesh->vertexData = new Ogre::VertexData();
		// Set number of indexes
		pSubmesh->indexData->indexCount = 3 * m_faces.size();
		pSubmesh->vertexData->vertexCount = m_vertices.size();
#else
		pSubmesh->vertexData[0] = new Ogre::v1::VertexData();
		// Set number of indexes
		pSubmesh->indexData[0]->indexCount = 3 * m_faces.size();
		pSubmesh->vertexData[0]->vertexCount = m_vertices.size();

		pSubmesh->vertexData[1] = new Ogre::v1::VertexData();
		// Set number of indexes
		pSubmesh->indexData[1]->indexCount = 3 * m_faces.size();
		pSubmesh->vertexData[1]->vertexCount = m_vertices.size();
#endif
        // Check if we need to use 32 bit indexes
        bool use32BitIndexes = false;
        if (m_vertices.size() > 65536 || params.useSharedGeom)
        {
            use32BitIndexes = true;
        }
        // Create a new index buffer
#if OGRE_VERSION < 0x020000
        pSubmesh->indexData->indexBuffer = 
            Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(
                use32BitIndexes ? Ogre::HardwareIndexBuffer::IT_32BIT : Ogre::HardwareIndexBuffer::IT_16BIT,
                pSubmesh->indexData->indexCount,
                Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
#else
		pSubmesh->indexData[0]->indexBuffer =
			Ogre::v1::HardwareBufferManager::getSingleton().createIndexBuffer(
			use32BitIndexes ? Ogre::v1::HardwareIndexBuffer::IT_32BIT : Ogre::v1::HardwareIndexBuffer::IT_16BIT,
			pSubmesh->indexData[0]->indexCount,
			Ogre::v1::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
#endif
        // Fill the index buffer with faces data
        if (use32BitIndexes)
        {
#if OGRE_VERSION < 0x020000
            Ogre::uint32* pIdx = static_cast<Ogre::uint32*>(
                pSubmesh->indexData->indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
#else
			Ogre::uint32* pIdx = static_cast<Ogre::uint32*>(
				pSubmesh->indexData[0]->indexBuffer->lock(Ogre::v1::HardwareBuffer::HBL_DISCARD));
#endif
            for (i=0; i<m_faces.size(); i++)
            {
                *pIdx++ = static_cast<Ogre::uint32>(m_faces[i].v[0]);
                *pIdx++ = static_cast<Ogre::uint32>(m_faces[i].v[1]);
                *pIdx++ = static_cast<Ogre::uint32>(m_faces[i].v[2]);
            }
#if OGRE_VERSION < 0x020000
            pSubmesh->indexData->indexBuffer->unlock();
#else
			pSubmesh->indexData[0]->indexBuffer->unlock();
#endif
        }
        else
        {
#if OGRE_VERSION < 0x020000
            Ogre::uint16* pIdx = static_cast<Ogre::uint16*>(
                pSubmesh->indexData->indexBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
#else
			Ogre::uint16* pIdx = static_cast<Ogre::uint16*>(
				pSubmesh->indexData[0]->indexBuffer->lock(Ogre::v1::HardwareBuffer::HBL_DISCARD));
#endif
            for (i=0; i<m_faces.size(); i++)
            {
                *pIdx++ = static_cast<Ogre::uint16>(m_faces[i].v[0]);
                *pIdx++ = static_cast<Ogre::uint16>(m_faces[i].v[1]);
                *pIdx++ = static_cast<Ogre::uint16>(m_faces[i].v[2]);
            }
#if OGRE_VERSION < 0x020000
            pSubmesh->indexData->indexBuffer->unlock();
#else
			pSubmesh->indexData[0]->indexBuffer->unlock();
#endif
        }
        // Define vertex declaration (only if we're not using shared geometry)
        if(!params.useSharedGeom)
        {
#if OGRE_VERSION < 0x020000
            Ogre::VertexDeclaration* pDecl = pSubmesh->vertexData->vertexDeclaration;
#else
			Ogre::v1::VertexDeclaration* pDecl = pSubmesh->vertexData[0]->vertexDeclaration;
#endif
            unsigned buf = 0;
            size_t offset = 0;
            // Add vertex position
            pDecl->addElement(buf, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
#if OGRE_VERSION < 0x020000
            offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
#else
			offset += Ogre::v1::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
#endif
            // Add vertex normal
            if (params.exportVertNorm)
            {
                pDecl->addElement(buf, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
#if OGRE_VERSION < 0x020000
                offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
#else
				offset += Ogre::v1::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
#endif
            }
            // Add vertex colour
            if(params.exportVertCol)
            {
                pDecl->addElement(buf, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
#if OGRE_VERSION < 0x020000
                offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
#else
				offset += Ogre::v1::VertexElement::getTypeSize(Ogre::VET_COLOUR);
#endif
            }
            // Add texture coordinates (maximum of 8!)
            size_t texCoordsCount = m_vertices[0].texcoords.size();
            if( texCoordsCount > 8 )
            {
				FxOgreFBXLog( "ERRORBOXWARNING: There were too many sets of texture coordinates. Only the first 8 will be exported.\n");
                texCoordsCount = 8;
            }
            for (i=0; i<texCoordsCount; i++)
            {
#if OGRE_VERSION < 0x020000
                Ogre::VertexElementType uvType = Ogre::VertexElement::multiplyTypeCount(Ogre::VET_FLOAT1, 2);
                pDecl->addElement(buf, offset, uvType, Ogre::VES_TEXTURE_COORDINATES, static_cast<unsigned short>(i));
                offset += Ogre::VertexElement::getTypeSize(uvType);
#else
				Ogre::VertexElementType uvType = Ogre::v1::VertexElement::multiplyTypeCount(Ogre::VET_FLOAT1, 2);
				pDecl->addElement(buf, offset, uvType, Ogre::VES_TEXTURE_COORDINATES, static_cast<unsigned short>(i));
				offset += Ogre::v1::VertexElement::getTypeSize(uvType);
#endif
            }
#if OGRE_VERSION < 0x020000
            Ogre::VertexDeclaration* pOptimalDecl = pDecl->getAutoOrganisedDeclaration(
                params.exportVBA, params.exportBlendShapes || params.exportVertAnims, false);
#else
			Ogre::v1::VertexDeclaration* pOptimalDecl = pDecl->getAutoOrganisedDeclaration(
				params.exportVBA, params.exportBlendShapes || params.exportVertAnims, false);
#endif
            // Fill the vertex buffer using the newly created vertex declaration
            stat = createOgreVertexBuffer(pSubmesh,pDecl,m_vertices);
            // Write vertex bone assignements list
            if (params.exportVBA)
            {
                // Create a new vertex bone assignements list
#if OGRE_VERSION < 0x020000
                Ogre::SubMesh::VertexBoneAssignmentList vbas;
#else
				Ogre::v1::SubMesh::VertexBoneAssignmentList vbas;
#endif
                // Scan list of shared geometry vertices
                for (i=0; i<m_vertices.size(); i++)
                {
                    vertex v = m_vertices[i];
                    // Add all bone assignemnts for every vertex to the bone assignements list
                    for (j=0; j<v.vbas.size(); j++)
                    {
#if OGRE_VERSION < 0x020000
                        Ogre::VertexBoneAssignment vba;
#else
						Ogre::v1::VertexBoneAssignment vba;
#endif
                        vba.vertexIndex = static_cast<unsigned int>(i);
                        vba.boneIndex = v.vbas[j].jointIdx;
                        vba.weight = v.vbas[j].weight;
#if OGRE_VERSION < 0x020000
                        vbas.insert(Ogre::SubMesh::VertexBoneAssignmentList::value_type(i, vba));
#else
						vbas.insert(Ogre::v1::SubMesh::VertexBoneAssignmentList::value_type(i, vba));
#endif
                    }
                }
                // Rationalise the bone assignements list
                pSubmesh->parent->_rationaliseBoneAssignments(pSubmesh->vertexData[0]->vertexCount,vbas);
                // Add bone assignements to the submesh
#if OGRE_VERSION < 0x020000
                for (Ogre::SubMesh::VertexBoneAssignmentList::iterator bi = vbas.begin(); bi != vbas.end(); bi++)
#else
				for (Ogre::v1::SubMesh::VertexBoneAssignmentList::iterator bi = vbas.begin(); bi != vbas.end(); bi++)
#endif
                {
                    pSubmesh->addBoneAssignment(bi->second);
                }
                pSubmesh->_compileBoneAssignments();
            }
            pSubmesh->vertexData[0]->reorganiseBuffers(pOptimalDecl);
        }
        return true;
    }


    // Create an Ogre compatible vertex buffer
#if OGRE_VERSION < 0x020000
    bool Submesh::createOgreVertexBuffer(Ogre::SubMesh* pSubmesh,Ogre::VertexDeclaration* pDecl,const std::vector<vertex>& vertices)
#else
	bool Submesh::createOgreVertexBuffer(Ogre::v1::SubMesh* pSubmesh, Ogre::v1::VertexDeclaration* pDecl, const std::vector<vertex>& vertices)
#endif
    {
#if OGRE_VERSION < 0x020000
        Ogre::HardwareVertexBufferSharedPtr vbuf = 
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(pDecl->getVertexSize(0),
            pSubmesh->vertexData->vertexCount, 
            Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY );
#else
		Ogre::v1::HardwareVertexBufferSharedPtr vbuf = 
			Ogre::v1::HardwareBufferManager::getSingleton().createVertexBuffer(pDecl->getVertexSize(0),
			pSubmesh->vertexData[0]->vertexCount, 
			Ogre::v1::HardwareBuffer::HBU_STATIC_WRITE_ONLY );
#endif
        pSubmesh->vertexData[0]->vertexBufferBinding->setBinding(0, vbuf);
        size_t vertexSize = pDecl->getVertexSize(0);
#if OGRE_VERSION < 0x020000
		char* pBase = static_cast<char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));
        Ogre::VertexDeclaration::VertexElementList elems = pDecl->findElementsBySource(0);
        Ogre::VertexDeclaration::VertexElementList::iterator ei, eiend;
#else
		char* pBase = static_cast<char*>(vbuf->lock(Ogre::v1::HardwareBuffer::HBL_DISCARD));
		Ogre::v1::VertexDeclaration::VertexElementList elems = pDecl->findElementsBySource(0);
		Ogre::v1::VertexDeclaration::VertexElementList::iterator ei, eiend;
#endif
        eiend = elems.end();
        float* pFloat;
        Ogre::RGBA* pRGBA;
        // Fill the vertex buffer with shared geometry data
        unsigned long vi;
        Ogre::ColourValue col;
        float ucoord, vcoord;
        for (vi=0; vi<vertices.size(); vi++)
        {
            int iTexCoord = 0;
            vertex v = vertices[vi];
            for (ei = elems.begin(); ei != eiend; ++ei)
            {
#if OGRE_VERSION < 0x020000
                Ogre::VertexElement& elem = *ei;
#else
				Ogre::v1::VertexElement& elem = *ei;
#endif
                switch(elem.getSemantic())
                {
                case Ogre::VES_POSITION:
                    elem.baseVertexPointerToElement(pBase, &pFloat);
                    *pFloat++ = static_cast<float>(v.x);
                    *pFloat++ = static_cast<float>(v.y);
                    *pFloat++ = static_cast<float>(v.z);
                    break;
                case Ogre::VES_NORMAL:
                    elem.baseVertexPointerToElement(pBase, &pFloat);
                    *pFloat++ = static_cast<float>(v.n.x);
                    *pFloat++ = static_cast<float>(v.n.y);
                    *pFloat++ = static_cast<float>(v.n.z);
                    break;
                case Ogre::VES_DIFFUSE:
                    {
                        elem.baseVertexPointerToElement(pBase, &pRGBA);
                        Ogre::ColourValue col(v.r, v.g, v.b, v.a);
#if OGRE_VERSION < 0x020000
                        *pRGBA = Ogre::VertexElement::convertColourValue(col, 
                            Ogre::VertexElement::getBestColourVertexElementType());
#else
						*pRGBA = Ogre::v1::VertexElement::convertColourValue(col,
							Ogre::v1::VertexElement::getBestColourVertexElementType());
#endif
                    }
                    break;
                case Ogre::VES_TEXTURE_COORDINATES:
                    elem.baseVertexPointerToElement(pBase, &pFloat);
                    ucoord = v.texcoords[iTexCoord].u;
                    vcoord = v.texcoords[iTexCoord].v;
                    *pFloat++ = static_cast<float>(ucoord);
                    *pFloat++ = static_cast<float>(vcoord);
                    iTexCoord++;
                    break;
                }
            }
            pBase += vertexSize;
        }
        vbuf->unlock();
        return true;
    }

}; //end of namespace
