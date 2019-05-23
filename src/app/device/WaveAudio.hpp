#ifndef APP_CONTENT_WAVEAUDIO_HPP
#define APP_CONTENT_WAVEAUDIO_HPP
#include <AL/alut.h>
#include "IPlayableAudio.hpp"
#include "WaveAudio.hpp"
namespace mygame {
class WaveAudio : public IPlayableAudio {
       public:
        WaveAudio() = default;
        void load(const std::string& path) override;
        void play() const override;
        void unload(const std::string& path) override;

       private:
        ALuint src;
        ALuint buf;
};
}  // namespace mygame
#endif