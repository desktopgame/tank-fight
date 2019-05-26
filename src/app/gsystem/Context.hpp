#ifndef APP_GSYSTEM_GAMECONTEXT_HPP
#define APP_GSYSTEM_GAMECONTEXT_HPP
#include <memory>
#include <vector>
namespace mygame {
class Object;
namespace internal {
class Context {
        Context();
        ~Context() = default;

       public:
        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;
        Context(Context&&) = delete;
        Context& operator=(Context&&) = delete;

        static Context& getInstance();
        void add(const std::shared_ptr<Object>& obj);
        void remove(const std::shared_ptr<Object>& obj);
        std::shared_ptr<Object> at(size_t index) const;
        size_t count() const;
        std::vector<std::shared_ptr<Object> >::const_iterator cbegin() const;
        std::vector<std::shared_ptr<Object> >::const_iterator cend() const;

       private:
        std::vector<std::shared_ptr<Object> > roots;
};
}  // namespace internal
}  // namespace mygame
#endif