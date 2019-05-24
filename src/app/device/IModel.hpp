#ifndef APP_DEVICE_IMODEL_HPP
#define APP_DEVICE_IMODEL_HPP
#include <string>

namespace mygame {
class IModel {
       public:
        IModel() = default;
        ~IModel() = default;
        virtual void load(const std::string& path) = 0;
        virtual void unload(const std::string& path) = 0;
        virtual void draw() = 0;
};
}  // namespace mygame
#endif