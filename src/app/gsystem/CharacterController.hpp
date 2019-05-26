#ifndef APP_GSYSTEM_CHARACTERCONTROLLER_HPP
#define APP_GSYSTEM_CHARACTERCONTROLLER_HPP
#include "IComponent.hpp"
namespace mygame {
class CharacterController : public IComponent {
       public:
        CharacterController();
        void onUpdate(const std::shared_ptr<Object>& obj) override;
        void onDraw(const std::shared_ptr<Object>& obj) override;
        void onAwake(const std::shared_ptr<Object>& obj) override;
        void onStart(const std::shared_ptr<Object>& obj) override;

       private:
        // float rotateX;
        // float rotateY;
        // float rotateZ;
};
}  // namespace mygame
#endif