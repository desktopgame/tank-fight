#include "MP3Pipeline.hpp"
namespace gel {
MP3Pipeline::MP3Pipeline(const std::shared_ptr<AudioManager>& audioManager)
    : audioManager(audioManager) {}
bool MP3Pipeline::accept(const std::string& path) { return true; }

void MP3Pipeline::load(const std::string& path) {
        audioManager->loadWave(path);
}

void MP3Pipeline::unload(const std::string& path) {
        audioManager->unload(path);
}
}  // namespace gel
