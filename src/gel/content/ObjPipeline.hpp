#ifndef GEL_CONTENT_OBJPIPELINE_HPP
#define GEL_CONTENT_OBJPIPELINE_HPP
#include "IContentPipeline.hpp"
namespace gel {
class ModelManager;
class ObjPipeline : public IContentPipeline {
       public:
        ObjPipeline(const std::shared_ptr<ModelManager>& modelManager);

        bool accept(const std::string& path) override;
        void load(const std::string& path) override;
        void unload(const std::string& path) override;

       private:
        std::shared_ptr<ModelManager> modelManager;
};
}  // namespace gel
#endif