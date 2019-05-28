#include "ObjMaterial.hpp"
namespace gel {
ObjMaterial::ObjMaterial()
    : name(),
      color(),
      shininess(),
      texture(),
      textureNo(),
      triangles(),
      quads(),
      triVerId(),
      triNorId(),
      triUVId(),
      quadVerId(),
      quadNorId(),
      quadUVId() {}
}  // namespace gel