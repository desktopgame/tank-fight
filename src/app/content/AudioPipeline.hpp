#ifndef APP_CONTENT_AUDIOPIPELINE_HPP
#define APP_CONTENT_AUDIOPIPELINE_HPP
#include <memory>
#include "../device/AudioManager.hpp"
#include "IContentPipeline.hpp"

namespace mygame {
class AudioPipeline : public IContentPipeline {
       public:
        AudioPipeline(const std::shared_ptr<AudioManager>& audioManager);
        bool accept(const std::string& path) override;
        void load(const std::string& path) override;
        void unload(const std::string& path) override;

       private:
        std::shared_ptr<AudioManager> audioManager;
};
}  // namespace mygame
#endif