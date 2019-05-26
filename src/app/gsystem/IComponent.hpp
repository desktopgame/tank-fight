#ifndef APP_GSYSTEM_ICOMPONENT_HPP
#define APP_GSYSTEM_ICOMPONENT_HPP
#include <memory>
namespace mygame {
class Object;
class IComponent {
       public:
        IComponent() = default;
        virtual ~IComponent() = default;
        virtual void onUpdate(const std::shared_ptr<Object>& obj) = 0;
        virtual void onDraw(const std::shared_ptr<Object>& obj) = 0;
        virtual void onAwake(const std::shared_ptr<Object>& obj) = 0;
        virtual void onStart(const std::shared_ptr<Object>& obj) = 0;
};
}  // namespace mygame
#endif