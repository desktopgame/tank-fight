#ifndef APP_CONTENT_PLAYABLEAUDIO_HPP
#define APP_CONTENT_PLAYABLEAUDIO_HPP
#include <string>
namespace mygame {
class IPlayableAudio {
       public:
        IPlayableAudio() = default;
        ~IPlayableAudio() = default;
        virtual void load(const std::string& path) = 0;
        virtual void play() const = 0;
        virtual void unload(const std::string& path) = 0;
};
}  // namespace mygame
#endif