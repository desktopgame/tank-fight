#include "FbxModel.hpp"
#include <stdexcept>
namespace mygame {
FbxModel::FbxModel(FbxManager* fbxManager)
    : fbxManager(fbxManager),
      fbxScene(nullptr),
      vinfo(),
      aabb() {}

void FbxModel::load(const std::string& path) {
        this->fbxScene = FbxScene::Create(this->fbxManager, "");
        this->fbxImporter = FbxImporter::Create(this->fbxManager, "");
        if (!fbxImporter->Initialize(path.c_str())) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        if (!fbxImporter->Import(fbxScene)) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        FbxGeometryConverter geometryConverter(fbxManager);
        geometryConverter.Triangulate(fbxScene, true);
        auto rootNode = fbxScene->GetRootNode();
        std::vector<FbxMesh*> meshes;
        std::vector<Vector3> vvertex;
        collectMesh(rootNode, meshes);
        for(int i=0; i<meshes.size(); i++) {
                FbxMeshInfo meshInfo;
                mapVertex(meshes[i], meshInfo);
                mapVertexIndex(meshes[i], meshInfo);
                mapNormal(meshes[i], meshInfo);
                mapUV(meshes[i], meshInfo);
                mapMaterial(meshes[i], meshInfo);
                mapSide(meshes[i], meshInfo);
                vinfo.push_back(meshInfo);
                for(auto v3 : meshInfo.vertex) {
                        vvertex.push_back(v3);
                }
        }
        this->aabb = AABB(vvertex);
}

void FbxModel::unload(const std::string& path) {
        fbxImporter->Destroy();
        fbxScene->Destroy();
}

void FbxModel::draw() {
        for(auto& meshInfo : vinfo) {
                drawMeshInfo(meshInfo);
        }
}

AABB FbxModel::getAABB() const { return aabb; }

// private
void FbxModel::drawMeshInfo(FbxMeshInfo& meshInfo) {
glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        size_t size = meshInfo.materials.size();
        for (int i = 0; i < (signed)size; i++) {
                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
                             (const GLfloat*)&meshInfo.materials[i].color.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
                             (const GLfloat*)&meshInfo.materials[i].color.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
                             (const GLfloat*)&meshInfo.materials[i].color.specular);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,
                            meshInfo.materials[i].shininess);
                if (meshInfo.materials[i].textureNo > 0) {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,
                                      meshInfo.texId[meshInfo.materials[i].textureNo - 1]);
                } else {
                        glDisable(GL_TEXTURE_2D);
                        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                }
                if (meshInfo.materials[i].triangles.size() > 1) {
                        glVertexPointer(3, GL_FLOAT, sizeof(Triangle),
                                        &meshInfo.materials[i].triangles[0].ver.x);
                        glNormalPointer(GL_FLOAT, sizeof(Triangle),
                                        &meshInfo.materials[i].triangles[0].nor.x);
                        if (meshInfo.materials[i].textureNo > 0)
                                glTexCoordPointer(
                                    2, GL_FLOAT, sizeof(Triangle),
                                    &meshInfo.materials[i].triangles[0].uv.u);
                        glDrawArrays(GL_TRIANGLES, 0,
                                     meshInfo.materials[i].triangles.size());
                }
                if (meshInfo.materials[i].quads.size() > 1) {
                        glVertexPointer(3, GL_FLOAT, sizeof(Quadrangle),
                                        &meshInfo.materials[i].quads[0].ver.x);
                        glNormalPointer(GL_FLOAT, sizeof(Quadrangle),
                                        &meshInfo.materials[i].quads[0].nor.x);
                        if (meshInfo.materials[i].textureNo > 0)
                                glTexCoordPointer(2, GL_FLOAT,
                                                  sizeof(Quadrangle),
                                                  &meshInfo.materials[i].quads[0].uv.u);
                        glDrawArrays(GL_QUADS, 0, meshInfo.materials[i].quads.size());
                }
                glPopMatrix();
        }
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
}

void FbxModel::collectRecMesh(FbxNode* rootNode, std::vector<FbxMesh*>& dest) {
        FbxMesh* fbxMesh = NULL;
        FbxNodeAttribute::EType type;
        FbxNodeAttribute* attr = rootNode->GetNodeAttribute();
        if (attr != NULL) {
                type = attr->GetAttributeType();
                if (type == FbxNodeAttribute::EType::eMesh) {
                        fbxMesh = rootNode->GetMesh();
                        dest.push_back(fbxMesh);
                } else {
                        collectMesh(rootNode, dest);
                }
        } else {
                collectMesh(rootNode, dest);
        }
}
void FbxModel::collectMesh(FbxNode* rootNode, std::vector<FbxMesh*>& dest) {
        FbxMesh* fbxMesh = NULL;
        int childCount = rootNode->GetChildCount();
        for (int i = 0; i < childCount; i++) {
                FbxNode* childNode = rootNode->GetChild(i);
                auto attr = childNode->GetNodeAttribute();
                auto type = attr->GetAttributeType();
                if (type == FbxNodeAttribute::EType::eMesh) {
                        fbxMesh = childNode->GetMesh();
                        dest.push_back(fbxMesh);
                } else {
                        collectRecMesh(childNode, dest);
                }
        }
}
FbxMesh* FbxModel::mapVertex(FbxMesh* fbxMesh, FbxMeshInfo& dest) {
        FbxVector4* coord = fbxMesh->GetControlPoints();
        for (int i = 0; i < fbxMesh->GetControlPointsCount(); i++) {
                float x = (float)coord[i][0];
                float y = (float)coord[i][1];
                float z = (float)coord[i][2];
                dest.vertex.push_back(Vector3(x, y, z));
        }
}
FbxMesh* FbxModel::mapVertexIndex(FbxMesh* fbxMesh, FbxMeshInfo& dest) {
        int* vindex = fbxMesh->GetPolygonVertices();
        for (int i = 0; i < fbxMesh->GetPolygonCount() * 3; i++) {
                dest.vertexIndex.push_back(vindex[i]);
        }
}
FbxMesh* FbxModel::mapNormal(FbxMesh* fbxMesh, FbxMeshInfo& dest) {
        FbxLayerElementNormal* elementNormal =
            fbxMesh->GetLayer(0)->GetNormals();
        if (elementNormal->GetMappingMode() ==
            FbxLayerElement::eByPolygonVertex) {
                if (elementNormal->GetReferenceMode() ==
                    FbxLayerElement::eDirect) {
                        for (int i = 0;
                             i < elementNormal->GetDirectArray().GetCount();
                             i++) {
                                float x = (float)elementNormal->GetDirectArray()
                                              .GetAt(i)[0];
                                float y = (float)elementNormal->GetDirectArray()
                                              .GetAt(i)[1];
                                float z = (float)elementNormal->GetDirectArray()
                                              .GetAt(i)[2];
                                dest.normal.push_back(Vector3(x, y, z));
                        }
                } else {
                        throw std::logic_error("unsupported file structure");
                }
        } else if (elementNormal->GetMappingMode() ==
                   FbxLayerElement::eByControlPoint) {
                if (elementNormal->GetReferenceMode() ==
                    FbxLayerElement::eDirect) {
                        for (int i = 0;
                             i < elementNormal->GetDirectArray().GetCount();
                             i++) {
                                float x = (float)elementNormal->GetDirectArray()
                                              .GetAt(i)[0];
                                float y = (float)elementNormal->GetDirectArray()
                                              .GetAt(i)[1];
                                float z = (float)elementNormal->GetDirectArray()
                                              .GetAt(i)[2];
                                dest.normal.push_back(Vector3(x, y, z));
                        }
                } else {
                        throw std::logic_error("unsupported file structure");
                }
        } else {
                throw std::logic_error("unsupported file structure");
        }
}
FbxMesh* FbxModel::mapUV(FbxMesh* fbxMesh, FbxMeshInfo& dest) {
        FbxLayerElementUV* uvs = fbxMesh->GetLayer(0)->GetUVs();
        int uvsize = std::max(uvs->GetIndexArray().GetCount(),
                              uvs->GetDirectArray().GetCount());
        FbxLayerElement::EMappingMode map = uvs->GetMappingMode();
        FbxLayerElement::EReferenceMode ref = uvs->GetReferenceMode();
        if (map == FbxLayerElement::eByPolygonVertex) {
                if (ref == FbxLayerElement::eDirect) {
                        for (int i = 0; i < uvsize; i++) {
                                FbxVector2 v2 = uvs->GetDirectArray().GetAt(i);
                                dest.uv.push_back(
                                    UV((float)v2[0], 1.0f - (float)v2[1]));
                        }
                } else if (ref == FbxLayerElement::eIndexToDirect) {
                        for (int i = 0; i < uvsize; i++) {
                                int index = uvs->GetIndexArray().GetAt(i);
                                FbxVector2 v2 =
                                    uvs->GetDirectArray().GetAt(index);
                                dest.uv.push_back(
                                    UV((float)v2[0], 1.0f - (float)v2[1]));
                        }
                } else {
                        throw std::logic_error("unsupported file structure");
                }
        } else {
                throw std::logic_error("unsupported file structure");
        }
}
FbxMesh* FbxModel::mapMaterial(FbxMesh* fbxMesh, FbxMeshInfo& dest) {
        FbxNode* node = fbxMesh->GetNode();
        for (int i = 0; i < node->GetMaterialCount(); i++) {
                FbxMaterial mtl;
                FbxSurfaceMaterial* material = node->GetMaterial(i);
                FbxSurfacePhong* phong =
                    dynamic_cast<FbxSurfacePhong*>(material);
                FbxPropertyT<FbxDouble3> d3ambient = phong->Ambient;
                mtl.color.ambient.r = (float)d3ambient.Get()[0];
                mtl.color.ambient.g = (float)d3ambient.Get()[1];
                mtl.color.ambient.b = (float)d3ambient.Get()[2];
                mtl.color.ambient.a = 1;
                FbxPropertyT<FbxDouble3> d3diffuse = phong->Diffuse;
                mtl.color.diffuse.r = (float)d3diffuse.Get()[0];
                mtl.color.diffuse.g = (float)d3diffuse.Get()[1];
                mtl.color.diffuse.b = (float)d3diffuse.Get()[2];
                mtl.color.diffuse.a = 1;
                FbxPropertyT<FbxDouble3> d3specular = phong->Specular;
                mtl.color.specular.r = (float)d3specular.Get()[0];
                mtl.color.specular.g = (float)d3specular.Get()[1];
                mtl.color.specular.b = (float)d3specular.Get()[2];
                mtl.color.specular.a = 1;
                mtl.shininess = phong->Shininess.Get();
                FbxProperty IProperty =
                    material->FindProperty(FbxSurfaceMaterial::sDiffuse);
                // FbxPropertyT<FbxDouble3> IProperty = phong->Diffuse;
                // FbxTexture* tex = FbxCast<FbxTexture>(
                // IProperty.GetSrcObject(FbxTexture::ClassId, 0));
                FbxFileTexture* tex = IProperty.GetSrcObject<FbxFileTexture>();
                if (tex) {
                        auto ptex = std::make_shared<PngTexture>();
                        ptex->load(tex->GetFileName());
                        dest.textures.push_back(ptex);
                        dest.texId.push_back(ptex->getID());
                        mtl.textureNo = dest.texId.size();
                        mtl.name = tex->GetFileName();
                }
                dest.materials.push_back(mtl);
                assert(!dest.materials.empty());
        }
}
FbxMesh* FbxModel::mapSide(FbxMesh* fbxMesh, FbxMeshInfo& dest) {
        assert(!dest.materials.empty());
        int count = 0;
        for (int k = 0; k < fbxMesh->GetPolygonCount(); k++) {
                FbxLayerElementMaterial* layerMat =
                    fbxMesh->GetLayer(0)->GetMaterials();
                int matId = layerMat->GetIndexArray().GetAt(k);
                int polygonSize = fbxMesh->GetPolygonSize(k);
                if (polygonSize == 3) {
                        for (int j = 0; j < 3; j++) {
                                Triangle tria;
                                tria.ver =
                                    dest.vertex[fbxMesh->GetPolygonVertex(k, j)];
                                tria.nor = dest.normal[count + j];
                                tria.uv = dest.uv[count + j];
                                dest.materials[matId].triangles.push_back(tria);
                        }
                        count += 3;
                } else if (polygonSize == 4) {
                        for (int j = 0; j < 4; j++) {
                                Quadrangle quad;
                                quad.ver =
                                    dest.vertex[fbxMesh->GetPolygonVertex(k, j)];
                                quad.nor = dest.normal[count + j];
                                quad.uv = dest.uv[count + j];
                                dest.materials[matId].quads.push_back(quad);
                        }
                        count += 4;
                     } else {
                        throw std::logic_error("unsupported file structure");
                }
        }
}
}  // namespace mygame