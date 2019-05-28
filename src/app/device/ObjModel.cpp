#include "ObjModel.hpp"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include "../model/Vector3.hpp"
#include "../model/Vector4.hpp"
#define BUFLEN (512)
namespace mygame {
ObjModel::ObjModel()
    : attrib(), shapes(), materials(), warn(), error(), aabb() {}

void ObjModel::load(const std::string& path) {
        std::set<char> delims{'/'};
        auto components = splitpath(path, delims);
        auto fn = components.back();
        components.pop_back();
        std::string dir;
        for (auto c : components) {
                dir += (c + "/");
        }
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &error,
                                    path.c_str());

        if (!error.empty()) std::cerr << error << std::endl;

        if (!ret) exit(1);
}

void ObjModel::unload(const std::string& path) {}

void ObjModel::draw() {
        for (const auto& shape : shapes) {
                // shape の名前
                std::cout << shape.name << std::endl;

                size_t index_offset = 0;  // インデントのオフセット
                for (size_t f = 0; f < shape.mesh.num_face_vertices.size();
                     f++) {
                        // 面 f を構成sする頂点の数
                        int num_vertices = shape.mesh.num_face_vertices[f];

                        glBegin(GL_TRIANGLES);
                        for (size_t v = 0; v < num_vertices; v++) {
                                // access to vertex
                                tinyobj::index_t idx =
                                    shape.mesh.indices[index_offset + v];

                                // 頂点の座標
                                float vx =
                                    attrib.vertices[3 * idx.vertex_index + 0];
                                float vy =
                                    attrib.vertices[3 * idx.vertex_index + 1];
                                float vz =
                                    attrib.vertices[3 * idx.vertex_index + 2];

                                // 頂点の法線
                                float nx =
                                    attrib.normals[3 * idx.normal_index + 0];
                                float ny =
                                    attrib.normals[3 * idx.normal_index + 1];
                                float nz =
                                    attrib.normals[3 * idx.normal_index + 2];

                                // 頂点のテクスチャ座標
                                tinyobj::real_t tx =
                                    attrib
                                        .texcoords[2 * idx.texcoord_index + 0];
                                tinyobj::real_t ty =
                                    attrib
                                        .texcoords[2 * idx.texcoord_index + 1];

                                // 頂点の色
                                float red =
                                    attrib.colors[3 * idx.vertex_index + 0];
                                float green =
                                    attrib.colors[3 * idx.vertex_index + 1];
                                float blue =
                                    attrib.colors[3 * idx.vertex_index + 2];
                        }
                        index_offset += num_vertices;

                        // per-face material
                        shape.mesh.material_ids[f];
                }
        }
}

AABB ObjModel::getAABB() const { return aabb; }

std::vector<std::string> ObjModel::splitpath(const std::string& str,
                                             const std::set<char> delimiters) {
        std::vector<std::string> result;

        char const* pch = str.c_str();
        char const* start = pch;
        for (; *pch; ++pch) {
                if (delimiters.find(*pch) != delimiters.end()) {
                        if (start != pch) {
                                std::string str(start, pch);
                                result.push_back(str);
                        } else {
                                result.push_back("");
                        }
                        start = pch + 1;
                }
        }
        result.push_back(start);

        return result;
}
}  // namespace mygame