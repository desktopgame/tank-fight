#ifndef APP_DEVICE_AUDIOMANAGER_HPP
#define APP_DEVICE_AUDIOMANAGER_HPP
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace mygame {
class IPlayableAudio;
class AudioManager {
       public:
        AudioManager();
        void load(const std::string& path);
        void play(const std::string& path) const;
        GLuint getBuffer(const std::string& path) const;
        GLuint getSource(const std::string& path) const;
        void unload(const std::string& path);

       private:
        std::unordered_map<std::string, std::shared_ptr<IPlayableAudio> >
            audioMap;
};
}  // namespace mygame
#endif