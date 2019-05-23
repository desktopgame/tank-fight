#include "AudioManager.hpp"
#include "WaveAudio.hpp"

namespace mygame {
AudioManager::AudioManager() : audioMap() {}
void AudioManager::load(const std::string& path) {
        auto playable = std::make_shared<WaveAudio>();
        playable->load(path);
        audioMap[path] = playable;
}

void AudioManager::play(const std::string& path) const {
        if (audioMap.count(path)) {
                audioMap.at(path)->play();
        }
}

void AudioManager::unload(const std::string& path) {
        if (audioMap.count(path)) {
                audioMap.erase(path);
        }
}
}  // namespace mygame