#include "AudioPipeline.hpp"
namespace mygame {
AudioPipeline::AudioPipeline(const std::shared_ptr<AudioManager>& audioManager)
    : audioManager(audioManager) {}
bool AudioPipeline::accept(const std::string& path) { return true; }

void AudioPipeline::load(const std::string& path) { audioManager->load(path); }

void AudioPipeline::unload(const std::string& path) {
        audioManager->unload(path);
}
}  // namespace mygame
