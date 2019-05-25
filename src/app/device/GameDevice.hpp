#ifndef APP_DEVICE_GAMEDEVICE_HPP
#define APP_DEVICE_GAMEDEVICE_HPP
#include <memory>
#include "../content/ContentManager.hpp"
#include "AudioManager.hpp"
#include "ModelManager.hpp"
#include "TextureManager.hpp"
namespace mygame {

class GameDevice {
       public:
        explicit GameDevice(const std::string& assetRootDir);
        static std::shared_ptr<GameDevice> make_shared(
            const std::string& assetRootDir);
        std::shared_ptr<ContentManager> getContentManager() const;
        std::shared_ptr<AudioManager> getAudioManager() const;
        std::shared_ptr<ModelManager> getModelManager() const;
        std::shared_ptr<TextureManager> getTextureManager() const;

       private:
        std::shared_ptr<ContentManager> contentManager;
        std::shared_ptr<AudioManager> audioManager;
        std::shared_ptr<ModelManager> modelManager;
        std::shared_ptr<TextureManager> textureManager;
};
}  // namespace mygame
#endif