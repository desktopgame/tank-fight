#ifndef APP_GSYSTEM_MODELRENDERER_HPP
#define APP_GSYSTEM_MODELRENDERER_HPP
#include <string>
#include "../device/ModelManager.hpp"
#include "IComponent.hpp"
namespace mygame {
class ModelRenderer : public IComponent {
       public:
        ModelRenderer(const std::string& path,
                      const std::shared_ptr<ModelManager>& modelManager);
        void onUpdate(const std::shared_ptr<Object>& obj) override;
        void onDraw(const std::shared_ptr<Object>& obj) override;
        void onAwake(const std::shared_ptr<Object>& obj) override;
        void onStart(const std::shared_ptr<Object>& obj) override;

       private:
        std::string path;
        std::shared_ptr<ModelManager> modelManager;
};
}  // namespace mygame
#endif