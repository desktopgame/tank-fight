#include "Context.hpp"
namespace mygame {
namespace internal {
Context::Context() : roots() {}

Context& Context::getInstance() {
        static Context instance;
        return instance;
}

void Context::add(const std::shared_ptr<Object>& obj) {
        this->roots.push_back(obj);
}

void Context::remove(const std::shared_ptr<Object>& obj) {
        auto iter = roots.begin();
        while (iter != roots.end()) {
                auto e = (*iter);
                if (e == obj) {
                        roots.erase(iter);
                        break;
                }
        }
}

std::shared_ptr<Object> Context::at(size_t index) const {
        return roots.at(index);
}

size_t Context::count() const { return roots.size(); }

std::vector<std::shared_ptr<Object> >::const_iterator Context::cbegin() const {
        return roots.cbegin();
}

std::vector<std::shared_ptr<Object> >::const_iterator Context::cend() const {
        return roots.cend();
}
}  // namespace internal
}  // namespace mygame