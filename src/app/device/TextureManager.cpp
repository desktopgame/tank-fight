#include "TextureManager.hpp"
#include "BmpTexture.hpp"
#include "ITexture.hpp"
namespace mygame {
TextureManager::TextureManager() : texMap() {}

void TextureManager::loadBmp(const std::string& path) {
        auto bmp = std::make_shared<BmpTexture>();
        bmp->load(path);
        texMap[path] = bmp;
}

GLuint TextureManager::getTextureID(const std::string& path) const {
        if (texMap.count(path)) {
                return texMap.at(path)->getTextureID();
        }
        ::abort();
}

void TextureManager::unload(const std::string& path) {
        if (texMap.count(path)) {
                texMap.at(path)->unload(path);
        }
        ::abort();
}
}  // namespace mygame