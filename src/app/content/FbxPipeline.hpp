#ifndef APP_CONTENT_FBXPIPELINE_HPP
#define APP_CONTENT_FBXPIPELINE_HPP
#include <memory>
#include <string>
#include "IContentPipeline.hpp"
namespace mygame {
class ModelManager;
class FbxPipeline : public IContentPipeline {
       public:
        FbxPipeline(const std::shared_ptr<ModelManager>& modelManager);

        bool accept(const std::string& path) override;
        void load(const std::string& path) override;
        void unload(const std::string& path) override;

       private:
        std::shared_ptr<ModelManager> modelManager;
};
}  // namespace mygame
#endif