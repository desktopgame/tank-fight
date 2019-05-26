#ifndef APP_GSYSTEM_RUNTIME_HPP
#define APP_GSYSTEM_RUNTIME_HPP
#include <memory>
#include <vector>
namespace mygame {
class Object;
class Runtime {
       private:
        Runtime();
        ~Runtime();

       public:
        static std::shared_ptr<Object> create(const std::string& name);
        static void destroy(const std::shared_ptr<Object>& obj);
        static std::shared_ptr<Object> findObjectWithTag(
            const std::string& tag);
        static std::vector<std::shared_ptr<Object> > findObjectsWithTag(
            const std::string& tag);
};
}  // namespace mygame
#endif