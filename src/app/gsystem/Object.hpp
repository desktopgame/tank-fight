#ifndef APP_GSYSTEM_GAMEOBJECT_HPP
#define APP_GSYSTEM_GAMEOBJECT_HPP
#include <memory>
#include <string>
#include <type_traits>
#include <vector>
#include "../model/Vector3.hpp"
#include "../model/Vector4.hpp"
namespace mygame {
class IComponent;
class Object : public std::enable_shared_from_this<Object> {
       public:
        explicit Object(const std::string& name);
        void setTag(const std::string& tag);
        std::string getTag() const;
        std::weak_ptr<Object> getParent() const;
        void addChild(const std::shared_ptr<Object>& child);
        std::shared_ptr<Object> getChildAt(size_t index) const;
        size_t getChildCount() const;
        void removeFromParent(bool attachToContext = true);

        void addComponent(const std::shared_ptr<IComponent>& comp);
        void removeComponent(const std::shared_ptr<IComponent>& comp);
        std::shared_ptr<IComponent> getComponentAt(size_t index);
        size_t getComponentCount() const;

        void onUpdate();
        void onDraw();
        void onAwake();
        void onStart();
        void onDestroy();

        Vector3 position;
        Vector3 scale;
        Vector3 rotate;
        float angle;

       private:
        void removeChild(const std::shared_ptr<Object> child);
        std::string name;
        std::string tag;
        std::vector<std::shared_ptr<Object> > children;
        std::vector<std::shared_ptr<IComponent> > components;
        std::weak_ptr<Object> parent;
};
}  // namespace mygame
#endif