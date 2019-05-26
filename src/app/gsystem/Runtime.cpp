#include "Runtime.hpp"
#include "Context.hpp"
#include "Object.hpp"
namespace mygame {

std::shared_ptr<Object> Runtime::create(const std::string& name) {
        auto ret = std::make_shared<Object>(name);
        internal::Context::getInstance().add(ret);
        ret->onAwake();
        return ret;
}

void Runtime::destroy(const std::shared_ptr<Object>& obj) {
        internal::Context::getInstance().remove(obj);
        obj->removeFromParent(false);
        obj->onDestroy();
}

std::shared_ptr<Object> Runtime::findObjectWithTag(const std::string& tag) {
        auto& inst = internal::Context::getInstance();
        auto iter = inst.cbegin();
        while (iter != inst.cend()) {
                auto e = (*iter);
                if (e->getTag() == tag) {
                        return e;
                }
        }
        return nullptr;
}
std::vector<std::shared_ptr<Object> > Runtime::findObjectsWithTag(
    const std::string& tag) {
        std::vector<std::shared_ptr<Object> > v;
        auto& inst = internal::Context::getInstance();
        auto iter = inst.cbegin();
        while (iter != inst.cend()) {
                auto e = (*iter);
                if (e->getTag() == tag) {
                        v.push_back(e);
                }
        }
        return v;
}
}  // namespace mygame