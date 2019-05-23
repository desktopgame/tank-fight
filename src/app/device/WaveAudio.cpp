#include "WaveAudio.hpp"
namespace mygame {
void WaveAudio::load(const std::string& path) {
        this->buf = alutCreateBufferFromFile(path.c_str());
        alGenSources(1, &(this->src));
        alSourcei(this->src, AL_BUFFER, this->buf);
}

void WaveAudio::play() const { alSourcePlay(this->src); }

void WaveAudio::unload(const std::string& path) {
        alDeleteBuffers(1, &(this->buf));
        alDeleteSources(1, &(this->src));
}
}  // namespace mygame