#include "FbxModel.hpp"
#include <stdexcept>
namespace mygame {
FbxModel::FbxModel(FbxManager* fbxManager)
    : fbxManager(fbxManager),
      fbxScene(nullptr),
      textures(),
      materials(),
      vertex(),
      normal(),
      uv(),
      vertexIndex(),
      texId() {}

void FbxModel::load(const std::string& path) {
        this->fbxScene = FbxScene::Create(this->fbxManager, "");
        this->fbxImporter = FbxImporter::Create(this->fbxManager, "");
        if (!fbxImporter->Initialize(path.c_str())) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        if (!fbxImporter->Import(fbxScene)) {
                throw std::logic_error("fatal error: FbxImporter#Initialize");
        }
        auto rootNode = fbxScene->GetRootNode();
        auto fbxMesh = findMesh(rootNode);
        mapVertex(fbxMesh);
        mapVertexIndex(fbxMesh);
        mapNormal(fbxMesh);
        mapUV(fbxMesh);
        mapMaterial(fbxMesh);
        mapSide(fbxMesh);
        vertex.clear();
        normal.clear();
        uv.clear();
        vertexIndex.clear();
}

void FbxModel::unload(const std::string& path) {
        fbxImporter->Destroy();
        fbxScene->Destroy();
}

void FbxModel::draw() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        for (int i = 0; i < materials.size(); i++) {
                glPushMatrix();
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,
                             (const GLfloat*)&materials[i].color.ambient);
                glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,
                             (const GLfloat*)&materials[i].color.diffuse);
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,
                             (const GLfloat*)&materials[i].color.specular);
                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,
                            materials[i].shininess);
                if (materials[i].textureNo > 0) {
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        glEnable(GL_TEXTURE_2D);
                        glBindTexture(GL_TEXTURE_2D,
                                      texId[materials[i].textureNo - 1]);
                } else {
                        glDisable(GL_TEXTURE_2D);
                        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                }
                if (materials[i].triangles.size() > 1) {
                        glVertexPointer(3, GL_FLOAT, sizeof(Triangle),
                                        &materials[i].triangles[0].ver.x);
                        glNormalPointer(GL_FLOAT, sizeof(Triangle),
                                        &materials[i].triangles[0].nor.x);
                        if (materials[i].textureNo > 0)
                                glTexCoordPointer(
                                    2, GL_FLOAT, sizeof(Triangle),
                                    &materials[i].triangles[0].uv.u);
                        glDrawArrays(GL_TRIANGLES, 0,
                                     materials[i].triangles.size());
                }
                if (materials[i].quads.size() > 1) {
                        glVertexPointer(3, GL_FLOAT, sizeof(Quadrangle),
                                        &materials[i].quads[0].ver.x);
                        glNormalPointer(GL_FLOAT, sizeof(Quadrangle),
                                        &materials[i].quads[0].nor.x);
                        if (materials[i].textureNo > 0)
                                glTexCoordPointer(2, GL_FLOAT,
                                                  sizeof(Quadrangle),
                                                  &materials[i].quads[0].uv.u);
                        glDrawArrays(GL_QUADS, 0, materials[i].quads.size());
                }
                glPopMatrix();
        }
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
        GLenum error_code = glGetError();
        if (error_code != GL_NO_ERROR) {
                ::abort();
        }
}

// private
FbxMesh* FbxModel::findRecMesh(FbxNode* rootNode) {
        FbxMesh* fbxMesh = NULL;
        FbxNodeAttribute::EType type;
        FbxNodeAttribute* attr = rootNode->GetNodeAttribute();
        if (attr != NULL) {
                type = attr->GetAttributeType();
                if (type == FbxNodeAttribute::EType::eMesh) {
                        fbxMesh = rootNode->GetMesh();
                } else {
                        fbxMesh = findMesh(rootNode);
                }
        } else {
                fbxMesh = findMesh(rootNode);
        }
        return fbxMesh;
}
FbxMesh* FbxModel::findMesh(FbxNode* rootNode) {
        FbxMesh* fbxMesh = NULL;
        int childCount = rootNode->GetChildCount();
        for (int i = 0; i < childCount; i++) {
                if (fbxMesh != NULL) {
                        break;
                }
                FbxNode* childNode = rootNode->GetChild(i);
                auto attr = childNode->GetNodeAttribute();
                auto type = attr->GetAttributeType();
                if (type == FbxNodeAttribute::EType::eMesh) {
                        fbxMesh = childNode->GetMesh();
                } else {
                        fbxMesh = findRecMesh(childNode);
                }
        }
        return fbxMesh;
}
FbxMesh* FbxModel::mapVertex(FbxMesh* fbxMesh) {
        FbxVector4* coord = fbxMesh->GetControlPoints();
        for (int i = 0; i < fbxMesh->GetControlPointsCount(); i++) {
                float x = (float)coord[i][0];
                float y = (float)coord[i][1];
                float z = (float)coord[i][2];
                this->vertex.push_back(Vector3(x, y, z));
        }
}
FbxMesh* FbxModel::mapVertexIndex(FbxMesh* fbxMesh) {
        int* vindex = fbxMesh->GetPolygonVertices();
        for (int i = 0; i < fbxMesh->GetPolygonCount() * 3; i++) {
                this->vertexIndex.push_back(vindex[i]);
        }
}
FbxMesh* FbxModel::mapNormal(FbxMesh* fbxMesh) {
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
                                normal.push_back(Vector3(x, y, z));
                        }
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
                                normal.push_back(Vector3(x, y, z));
                        }
                }
        }
}
FbxMesh* FbxModel::mapUV(FbxMesh* fbxMesh) {
        FbxLayerElementUV* uvs = fbxMesh->GetLayer(0)->GetUVs();
        int uvsize = std::max(uvs->GetIndexArray().GetCount(),
                              uvs->GetDirectArray().GetCount());
        FbxLayerElement::EMappingMode map = uvs->GetMappingMode();
        FbxLayerElement::EReferenceMode ref = uvs->GetReferenceMode();
        if (map == FbxLayerElement::eByPolygonVertex) {
                if (ref == FbxLayerElement::eDirect) {
                        for (int i = 0; i < uvsize; i++) {
                                FbxVector2 v2 = uvs->GetDirectArray().GetAt(i);
                                uv.push_back(
                                    UV((float)v2[0], 1.0f - (float)v2[1]));
                        }
                } else if (ref == FbxLayerElement::eIndexToDirect) {
                        for (int i = 0; i < uvsize; i++) {
                                int index = uvs->GetIndexArray().GetAt(i);
                                FbxVector2 v2 =
                                    uvs->GetDirectArray().GetAt(index);
                                uv.push_back(
                                    UV((float)v2[0], 1.0f - (float)v2[1]));
                        }
                }
        }
}
FbxMesh* FbxModel::mapMaterial(FbxMesh* fbxMesh) {
        FbxNode* node = fbxMesh->GetNode();
        for (int i = 0; i < node->GetMaterialCount(); i++) {
                Material mtl;
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
                mtl.shininess = 0.5f;
                FbxProperty IProperty =
                    material->FindProperty(FbxSurfaceMaterial::sDiffuse);
                // FbxPropertyT<FbxDouble3> IProperty = phong->Diffuse;
                // FbxTexture* tex = FbxCast<FbxTexture>(
                // IProperty.GetSrcObject(FbxTexture::ClassId, 0));
                FbxFileTexture* tex = IProperty.GetSrcObject<FbxFileTexture>();
                if (tex) {
                        auto ptex = std::make_shared<PngTexture>();
                        ptex->load(tex->GetFileName());
                        textures.push_back(ptex);
                        texId.push_back(ptex->getID());
                        mtl.textureNo = texId.size();
                        mtl.name = tex->GetFileName();
                }
                materials.push_back(mtl);
                assert(!materials.empty());
        }
}
FbxMesh* FbxModel::mapSide(FbxMesh* fbxMesh) {
        assert(!materials.empty());
        int count = 0;
        for (int k = 0; k < fbxMesh->GetPolygonCount(); k++) {
                FbxLayerElementMaterial* layerMat =
                    fbxMesh->GetLayer(0)->GetMaterials();
                int matId = layerMat->GetIndexArray().GetAt(k);
                if (fbxMesh->GetPolygonSize(k) == 3) {
                        for (int j = 0; j < 3; j++) {
                                Triangle tria;
                                tria.ver =
                                    vertex[fbxMesh->GetPolygonVertex(k, j)];
                                tria.nor = normal[count + j];
                                tria.uv = uv[count + j];
                                materials[matId].triangles.push_back(tria);
                        }
                        count += 3;
                }
                if (fbxMesh->GetPolygonSize(k) == 4) {
                        for (int j = 0; j < 4; j++) {
                                Quadrangle quad;
                                quad.ver =
                                    vertex[fbxMesh->GetPolygonVertex(k, j)];
                                quad.nor = normal[count + j];
                                quad.uv = uv[count + j];
                                materials[matId].quads.push_back(quad);
                        }
                        count += 4;
                }
        }
}
}  // namespace mygame