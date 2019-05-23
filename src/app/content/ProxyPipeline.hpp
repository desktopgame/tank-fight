#ifndef APP_CONTENT_PROXYPIPELINE_H
#define APP_CONTENT_PROXYPIPELINE_H
#include <memory>
#include <string>
#include "IContentPipeline.hpp"

namespace mygame {
template <typename T>
class ProxyPipeline : public IContentPipeline {
       public:
        template <typename... Args>
        ProxyPipeline(const std::string& extension, Args... args);
        bool accept(const std::string& path) override;
        void load(const std::string& path) override;
        void unload(const std::string& path) override;

       private:
        std::string extension;
        std::shared_ptr<T> proxy;
};
template <typename T>
template <typename... Args>
ProxyPipeline<T>::ProxyPipeline(const std::string& extension, Args... args) {
        this->extension = extension;
        this->proxy = std::make_shared<T>(args...);
}
template <typename T>
bool ProxyPipeline<T>::accept(const std::string& path) {
        return (path.size() >= extension.size() &&
                path.find(extension, path.size() - extension.size()) !=
                    std::string::npos);
}

template <typename T>
void ProxyPipeline<T>::load(const std::string& path) {
        // T requires load method
        proxy->load(path);
}

template <typename T>
void ProxyPipeline<T>::unload(const std::string& path) {
        // T requires unload method
        proxy->unload(path);
}
}  // namespace mygame
#endif