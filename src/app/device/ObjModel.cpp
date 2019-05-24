#include "ObjModel.hpp"
#include <stdio.h>
#include "../model/Vector3.hpp"
#include "../model/Vector4.hpp"
#define BUFLEN (512)
namespace mygame {
ObjModel::ObjModel() : materials(), textures(), texId() {}

void ObjModel::load(const std::string& path) {
        Vector4 face[3];
        std::vector<Vector3> vertex;
        std::vector<Vector3> normal;
        std::vector<UV> uv;
        Vector3 bufv3;
        UV bufuv;
        int matNo = 0;
        char key[BUFLEN] = {0};
        FILE* fp = fopen(path.c_str(), "rt");
        if (fp == NULL) {
                perror("ObjModel#load");
                return;
        }
        fseek(fp, SEEK_SET, 0);
        while (!feof(fp)) {
                // FIXME: buffer overflow.
                memset(key, '\0', sizeof(char) * BUFLEN);
                fscanf(fp, "%s ", key);
                if (!::strcmp(key, "mtllib")) {
                        fscanf(fp, "%s ", key);
                        loadMaterialFromFile(pathToDir(path), key);
                }
                if (!::strcmp(key, "v")) {
                        fscanf(fp, "%f %f %f", &bufv3.x, &bufv3.y, &bufv3.z);
                        vertex.push_back(bufv3);
                }
                if (!::strcmp(key, "vn")) {
                        fscanf(fp, "%f %f %f", &bufv3.x, &bufv3.y, &bufv3.z);
                        normal.push_back(bufv3);
                }
                if (!::strcmp(key, "vt")) {
                        fscanf(fp, "%f %f", &bufuv.u, &bufuv.v);
                        uv.push_back(bufuv);
                }
                if (!::strcmp(key, "usemtl")) {
                        fscanf(fp, "%s ", key);
                        for (int i = 0; i < materials.size(); i++) {
                                if (!::strcmp(key, materials[i].name.c_str())) {
                                        matNo = i;
                                }
                        }
                }
                if (!::strcmp(key, "f")) {
                        face[0].w = -1;
                        face[1].w = -1;
                        face[2].w = -1;
                        fscanf(fp, "%f/%f/%f %f/%f/%f %f/%f/%f %f/%f/%f",
                               &face[0].x, &face[1].x, &face[2].x, &face[0].y,
                               &face[1].y, &face[2].y, &face[0].z, &face[1].z,
                               &face[2].z, &face[0].w, &face[1].w, &face[2].w);
                        if (face[0].w == -1 && face[1].w == -1 &&
                            face[2].w == -1) {
                                materials[matNo].triVerId.push_back(face[0].x -
                                                                    1);
                                materials[matNo].triVerId.push_back(face[0].y -
                                                                    1);
                                materials[matNo].triVerId.push_back(face[0].z -
                                                                    1);
                                materials[matNo].triUVId.push_back(face[1].x -
                                                                   1);
                                materials[matNo].triUVId.push_back(face[1].y -
                                                                   1);
                                materials[matNo].triUVId.push_back(face[1].z -
                                                                   1);
                                materials[matNo].triNorId.push_back(face[2].x -
                                                                    1);
                                materials[matNo].triNorId.push_back(face[2].y -
                                                                    1);
                                materials[matNo].triNorId.push_back(face[2].z -
                                                                    1);
                        } else {
                                materials[matNo].quadVerId.push_back(face[0].x -
                                                                     1);
                                materials[matNo].quadVerId.push_back(face[0].y -
                                                                     1);
                                materials[matNo].quadVerId.push_back(face[0].z -
                                                                     1);
                                materials[matNo].quadVerId.push_back(face[0].w -
                                                                     1);
                                materials[matNo].quadUVId.push_back(face[1].x -
                                                                    1);
                                materials[matNo].quadUVId.push_back(face[1].y -
                                                                    1);
                                materials[matNo].quadUVId.push_back(face[1].z -
                                                                    1);
                                materials[matNo].quadUVId.push_back(face[1].w -
                                                                    1);
                                materials[matNo].quadNorId.push_back(face[2].x -
                                                                     1);
                                materials[matNo].quadNorId.push_back(face[2].y -
                                                                     1);
                                materials[matNo].quadNorId.push_back(face[2].z -
                                                                     1);
                                materials[matNo].quadNorId.push_back(face[2].w -
                                                                     1);
                        }
                }
        }
        for (int j = 0; j < materials.size(); j++) {
                for (int i = 0; i < materials[j].triVerId.size(); i++) {
                        Triangle tria;
                        tria.ver = vertex[materials[j].triVerId[i]];
                        tria.nor = normal[materials[j].triNorId[i]];
                        tria.uv = uv[materials[j].triNorId[i]];
                        materials[j].triangles.push_back(tria);
                }
                for (int i = 0; i < materials[j].quadVerId.size(); i++) {
                        Quadrangle quad;
                        quad.ver = vertex[materials[j].quadVerId[i]];
                        quad.nor = normal[materials[j].quadNorId[i]];
                        quad.uv = uv[materials[j].quadUVId[i]];
                        materials[j].quads.push_back(quad);
                }
                materials[j].triVerId.clear();
                materials[j].triNorId.clear();
                materials[j].triUVId.clear();
                materials[j].quadVerId.clear();
                materials[j].quadNorId.clear();
                materials[j].quadUVId.clear();
        }
        vertex.clear();
        normal.clear();
        uv.clear();
}

void ObjModel::unload(const std::string& path) {}

void ObjModel::draw() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        for (int i = 0; i < (signed)materials.size(); i++) {
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
}

void ObjModel::loadMaterialFromFile(const std::string& dir, const char* path) {
        std::string resolved = (dir + '/' + path);
        FILE* fp = fopen(resolved.c_str(), "rt");
        if (fp == NULL) {
                perror("ObjModel#loadMaterialFromFile");
                return;
        }
        char key[BUFLEN] = {0};
        Vector4 bufv4;
        bool flag = false, flag2 = false;
        bufv4.w = 1.0f;
        ObjMaterial objMat;
        objMat.color.emission = (const Color4&)bufv4;
        objMat.shininess = 0;
        objMat.textureNo = 0;
        fseek(fp, SEEK_SET, 0);
        while (!feof(fp)) {
                fscanf(fp, "%s ", key);
                if (!::strcmp(key, "newmtl")) {
                        if (flag) {
                                materials.push_back(objMat);
                                objMat.textureNo = 0;
                        }
                        flag = true;
                        fscanf(fp, "%s ", key);
                        objMat.name = key;
                        flag2 = false;
                }
                if (!::strcmp(key, "Ka")) {
                        fscanf(fp, "%f %f %f", &bufv4.x, &bufv4.y, &bufv4.z);
                        objMat.color.ambient = (const Color4&)bufv4;
                }
                if (!::strcmp(key, "Kd")) {
                        fscanf(fp, "%f %f %f", &bufv4.x, &bufv4.y, &bufv4.z);
                        objMat.color.diffuse = (const Color4&)bufv4;
                }
                if (!::strcmp(key, "Ks")) {
                        fscanf(fp, "%f %f %f", &bufv4.x, &bufv4.y, &bufv4.z);
                        objMat.color.specular = (const Color4&)bufv4;
                }
                if (!::strcmp(key, "Ns")) {
                        fscanf(fp, "%f", &bufv4.x);
                        objMat.shininess = bufv4.x;
                }
                if (!::strcmp(key, "map_Kd")) {
                        fscanf(fp, "%s ", key);
                        for (int i = 0; i < materials.size(); i++) {
                                if (!::strcmp(key, materials[i].name.c_str())) {
                                        flag2 = true;
                                        objMat.textureNo =
                                            materials[i].textureNo;
                                        break;
                                }
                        }
                        if (!flag2) {
                                auto texpath = (dir + '/' + key);
                                objMat.texture = texpath;
                                auto tex = std::make_shared<PngTexture>();
                                tex->load(texpath);
                                textures.push_back(tex);
                                texId.push_back(tex->getID());
                                objMat.textureNo = texId.size();
                        }
                }
        }
        fclose(fp);
        if (flag) {
                materials.push_back(objMat);
        }
}

std::string ObjModel::pathToDir(const std::string& path) {
        std::string::size_type pos = path.rfind("/");
        if (pos == std::string::npos) {
                return ".";
        }
        return path.substr(0, pos);
}
}  // namespace mygame