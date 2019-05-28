#ifndef GEL_CONTENT_PNGPIPELINE_HPP
#define GEL_CONTENT_PNGPIPELINE_HPP
#include <memory>
#include <string>
#include "IContentPipeline.hpp"
namespace gel {
class TextureManager;
class PngPipeline : public IContentPipeline {
       public:
        PngPipeline(const std::shared_ptr<TextureManager>& textureManager);
        bool accept(const std::string& path) override;
        void load(const std::string& path) override;
        void unload(const std::string& path) override;

       private:
        std::shared_ptr<TextureManager> textureManager;
};
}  // namespace gel
#endif