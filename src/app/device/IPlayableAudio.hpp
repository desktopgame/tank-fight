#ifndef APP_DEVICE_PLAYABLEAUDIO_HPP
#define APP_DEVICE_PLAYABLEAUDIO_HPP
#include <GLFW/glfw3.h>
#include <string>
namespace mygame {
class IPlayableAudio {
       public:
        IPlayableAudio() = default;
        ~IPlayableAudio() = default;
        virtual void load(const std::string& path) = 0;
        virtual void play() const = 0;
        virtual GLuint getBuffer() const = 0;
        virtual GLuint getSource() const = 0;
        virtual void unload(const std::string& path) = 0;
};
}  // namespace mygame
#endif