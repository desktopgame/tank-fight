#ifndef APP_DEVICE_FBXMESHINFO_HPP
#define APP_DEVICE_FBXMESHINFO_HPP
#include "../model/Vector3.hpp"
#include "../model/UV.hpp"
#include "FbxMaterial.hpp"
#include "PngTexture.hpp"
#include <vector>
namespace mygame {
class FbxMeshInfo {
	public:
		FbxMeshInfo();
        std::vector<std::shared_ptr<PngTexture> > textures;
        std::vector<Vector3> vertex;
        std::vector<Vector3> normal;
        std::vector<FbxMaterial> materials;
        std::vector<UV> uv;
        std::vector<int> vertexIndex;
        std::vector<int> texId;
};
}
#endif