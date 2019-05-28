#include "ObjModel.hpp"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "../model/Vector3.hpp"
#include "../model/Vector4.hpp" #include < iostream >
#include "ObjFace.hpp"
#define BUFLEN (512)
namespace mygame {
ObjModel::ObjModel() : materials(), textures(), texId() {}

void ObjModel::load(const std::string& path) {
        std::vector<Vector3> vertex;
        std::vector<Vector3> normal;
        std::vector<UV> uv;
        Vector3 bufv3;
        UV bufuv;
        int matNo = 0;
        std::string line;
        std::ifstream ifs(path.c_str());
        if (!ifs.is_open()) {
                return;
        }
        int lineno = 0;
        while (std::getline(ifs, line)) {
                line = trimLeft(line);
                auto words = split(line, ' ');
                // skip if empty line or commented
                if (words.empty() || words[0] == "#") {
                        lineno++;
                        continue;
                }
                auto code = words[0];
                if (code == "mtllib") {
                        loadMaterialFromFile(pathToDir(path), words[1].c_str());
                } else if (code == "v") {
                        bufv3.x = tofloat(words[1]);
                        bufv3.y = tofloat(words[2]);
                        bufv3.z = tofloat(words[3]);
                        vertex.push_back(bufv3);
                } else if (code == "vn") {
                        bufv3.x = tofloat(words[1]);
                        bufv3.y = tofloat(words[2]);
                        bufv3.z = tofloat(words[3]);
                        normal.push_back(bufv3);
                } else if (code == "vt") {
                        bufuv.u = tofloat(words[1]);
                        bufuv.v = 1 - tofloat(words[2]);
                        uv.push_back(bufuv);
                } else if (code == "usemtl") {
                        for (int i = 0; i < materials.size(); i++) {
                                if (words[1] == materials[i].name) {
                                        matNo = i;
                                }
                        }
                } else if (code == "f") {
                        std::vector<ObjFace> vface;
                        auto polys = words.size() - 1;
                        for (int i = 0; i < polys; i++) {
                                ObjFace nface;
                                auto v = words[1 + i];
                                auto map = split(v, '/');
                                nface.vIndex = toint(map[0]);
                                nface.uvIndex = toint(map[1]);
                                nface.normalIndex = toint(map[2]);
                                vface.push_back(nface);
                        }
                        // xxx yyy zzz www
                        // x   y   z   w
                        // x   y   z   w
                        if (polys == 3) {
                                materials[matNo].triVerId.push_back(
                                    vface[0].vIndex - 1);
                                materials[matNo].triVerId.push_back(
                                    vface[1].vIndex - 1);
                                materials[matNo].triVerId.push_back(
                                    vface[2].vIndex - 1);
                                materials[matNo].triUVId.push_back(
                                    vface[0].uvIndex - 1);
                                materials[matNo].triUVId.push_back(
                                    vface[1].uvIndex - 1);
                                materials[matNo].triUVId.push_back(
                                    vface[2].uvIndex - 1);
                                materials[matNo].triNorId.push_back(
                                    vface[0].normalIndex - 1);
                                materials[matNo].triNorId.push_back(
                                    vface[1].normalIndex - 1);
                                materials[matNo].triNorId.push_back(
                                    vface[2].normalIndex - 1);
                        } else if (polys == 4) {
                                materials[matNo].quadVerId.push_back(
                                    vface[0].vIndex - 1);
                                materials[matNo].quadVerId.push_back(
                                    vface[1].vIndex - 1);
                                materials[matNo].quadVerId.push_back(
                                    vface[2].vIndex - 1);
                                materials[matNo].quadVerId.push_back(
                                    vface[3].vIndex - 1);
                                materials[matNo].quadUVId.push_back(
                                    vface[0].uvIndex - 1);
                                materials[matNo].quadUVId.push_back(
                                    vface[1].uvIndex - 1);
                                materials[matNo].quadUVId.push_back(
                                    vface[2].uvIndex - 1);
                                materials[matNo].quadUVId.push_back(
                                    vface[3].uvIndex - 1);
                                materials[matNo].quadNorId.push_back(
                                    vface[0].normalIndex - 1);
                                materials[matNo].quadNorId.push_back(
                                    vface[1].normalIndex - 1);
                                materials[matNo].quadNorId.push_back(
                                    vface[2].normalIndex - 1);
                                materials[matNo].quadNorId.push_back(
                                    vface[3].normalIndex - 1);
                        } else {
                                auto mseg =
                                    std::string("unsupported format: ") +
                                    std::to_string(lineno);
                                throw std::logic_error(mseg);
                        }
                } else {
                        std::cout << "no operation: " << line << std::endl;
                }
                lineno++;
        }
        auto vsize = vertex.size();
        auto nsize = normal.size();
        auto usize = uv.size();
        for (int j = 0; j < materials.size(); j++) {
                auto& mat = materials[j];
                for (int i = 0; i < mat.triVerId.size(); i++) {
                        Triangle tria;
                        auto vid = mat.triVerId[i];
                        auto nid = mat.triNorId[i];
                        auto uid = mat.triUVId[i];
                        assert(vid >= 0 && vid < vsize);
                        assert(nid >= 0 && nid < nsize);
                        assert(uid >= 0 && uid < usize);
                        tria.ver = vertex[vid];
                        tria.nor = normal[nid];
                        tria.uv = uv[uid];
                        mat.triangles.push_back(tria);
                }
                for (int i = 0; i < mat.quadVerId.size(); i++) {
                        Quadrangle quad;
                        auto vid = mat.quadVerId[i];
                        auto nid = mat.quadNorId[i];
                        auto uid = mat.quadUVId[i];
                        assert(vid >= 0 && vid < vsize);
                        assert(nid >= 0 && nid < nsize);
                        assert(uid >= 0 && uid < usize);
                        quad.ver = vertex[vid];
                        quad.nor = normal[nid];
                        quad.uv = uv[uid];
                        mat.quads.push_back(quad);
                }
                mat.triVerId.clear();
                mat.triNorId.clear();
                mat.triUVId.clear();
                mat.quadVerId.clear();
                mat.quadNorId.clear();
                mat.quadUVId.clear();
        }
        this->aabb = AABB(vertex);
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

AABB ObjModel::getAABB() const { return aabb; }

std::string ObjModel::trimLeft(const std::string& src) {
        int pos = 0;
        for (auto c : src) {
                if (c != ' ' && c != '\t') {
                        return src.substr(pos, src.size() - pos);
                }
                pos++;
        }
        return "";
}

std::vector<std::string> ObjModel::split(const std::string& src, char c) {
        std::vector<std::string> a;
        std::string buf;
        for (int i = 0; i < src.size(); i++) {
                auto e = src[i];
                if (e != c) {
                        buf += e;
                } else if (e == c) {
                        a.push_back(buf);
                        buf.clear();
                }
        }
        if (buf.size() > 0) {
                a.push_back(buf);
        }
        return a;
}

float ObjModel::tofloat(const std::string& src) {
        return (float)::atof(src.c_str());
}

int ObjModel::toint(const std::string& src) { return ::atoi(src.c_str()); }

void ObjModel::loadMaterialFromFile(const std::string& dir, const char* path) {
        std::string resolved = (dir + '/' + path);
        std::string line;
        std::ifstream ifs(resolved.c_str());
        if (!ifs.is_open()) {
                return;
        }
        Vector4 bufv4;
        bool flag = false, flag2 = false;
        bufv4.w = 1.0f;
        ObjMaterial objMat;
        objMat.color.emission = (const Color4&)bufv4;
        objMat.shininess = 0;
        objMat.textureNo = 0;
        int lineno = 0;
        while (std::getline(ifs, line)) {
                line = trimLeft(line);
                auto words = split(line, ' ');
                if (words.empty() || words[0] == "#") {
                        continue;
                }
                auto code = words[0];
                if (code == "newmtl") {
                        if (flag) {
                                materials.push_back(objMat);
                                objMat.textureNo = 0;
                        }
                        flag = true;
                        objMat.name = words[1];
                        flag2 = false;
                } else if (code == "Ka") {
                        bufv4.x = tofloat(words[1]);
                        bufv4.y = tofloat(words[2]);
                        bufv4.z = tofloat(words[3]);
                        objMat.color.ambient = (const Color4&)bufv4;
                } else if (code == "Kd") {
                        bufv4.x = tofloat(words[1]);
                        bufv4.y = tofloat(words[2]);
                        bufv4.z = tofloat(words[3]);
                        objMat.color.diffuse = (const Color4&)bufv4;
                } else if (code == "Ks") {
                        bufv4.x = tofloat(words[1]);
                        bufv4.y = tofloat(words[2]);
                        bufv4.z = tofloat(words[3]);
                        objMat.color.specular = (const Color4&)bufv4;
                } else if (code == "Ns") {
                        objMat.shininess = tofloat(words[1]);
                } else if (code == "map_Kd") {
                        for (int i = 0; i < materials.size(); i++) {
                                if (words[1] == materials[i].texture) {
                                        flag2 = true;
                                        objMat.textureNo =
                                            materials[i].textureNo;
                                        break;
                                }
                        }
                        if (flag2) {
                        } else {
                                auto texpath = (dir + '/' + words[1]);
                                objMat.texture = words[1];
                                auto tex = std::make_shared<PngTexture>();
                                tex->load(texpath);
                                textures.push_back(tex);
                                texId.push_back(tex->getID());
                                objMat.textureNo = texId.size();
                        }
                } else {
                        std::cout << "no operation: " << line << std::endl;
                }
        }
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