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

std::shared_ptr<ITexture> TextureManager::getTexture(const std::string& path) {
        if (texMap.count(path)) {
                return texMap.at(path);
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