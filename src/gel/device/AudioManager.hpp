#ifndef GEL_DEVICE_AUDIOMANAGER_HPP
#define GEL_DEVICE_AUDIOMANAGER_HPP
#include <AL/alut.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace gel {
class IPlayableAudio;
/**
 * AudioManager is manage a `IPlayableAudio`
 * in now, supported a .wave only
 */
class AudioManager {
       public:
        AudioManager();
        /**
         * load a .wave file.
         * @param path
         */
        void loadWave(const std::string& path);
        /**
         * play audio.
         * should be load file in before call.
         * @param path
         */
        void play(const std::string& path) const;

        /**
         * return a buffer of OpenAL.
         * @param path
         * @return
         */
        ALuint getBuffer(const std::string& path) const;

        /**
         * return a source of OpenAL.
         * @param path
         * @return
         */
        ALuint getSource(const std::string& path) const;

        /**
         * unload audio.
         * @param path
         */
        void unload(const std::string& path);

       private:
        std::unordered_map<std::string, std::shared_ptr<IPlayableAudio> >
            audioMap;
};
}  // namespace gel
#endif