#ifndef GEL_CONTENT_MP3PIPELINE_HPP
#define GEL_CONTENT_MP3PIPELINE_HPP
#include <memory>
#include "../device/AudioManager.hpp"
#include "IContentPipeline.hpp"

namespace gel {
class MP3Pipeline : public IContentPipeline {
       public:
        MP3Pipeline(const std::shared_ptr<AudioManager>& audioManager);
        bool accept(const std::string& path) override;
        void load(const std::string& path) override;
        void unload(const std::string& path) override;

       private:
        std::shared_ptr<AudioManager> audioManager;
};
}  // namespace gel
#endif