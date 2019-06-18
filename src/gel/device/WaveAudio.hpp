#ifndef GEL_DEVICE_WAVEAUDIO_HPP
#define GEL_DEVICE_WAVEAUDIO_HPP
#include <AL/alut.h>
#include "IPlayableAudio.hpp"
#include "WaveAudio.hpp"
namespace gel {
class WaveAudio : public IPlayableAudio {
       public:
        WaveAudio() = default;
        void load(const std::string& path) override;
        void play() const override;
        ALuint getBuffer() const override;
        ALuint getSource() const override;
        void unload(const std::string& path) override;

       private:
        ALuint src;
        ALuint buf;
};
}  // namespace gel
#endif