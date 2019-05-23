#ifndef APP_CONTENT_CONTENTMANAGER_HPP
#define APP_CONTENT_CONTENTMANAGER_HPP
#include <memory>
#include <string>
#include <vector>

namespace mygame {
class IContentPipeline;
class ContentManager {
       public:
        ContentManager(const std::string& rootDir);
        void add(const std::shared_ptr<IContentPipeline>& pipe);
        void remove(const std::shared_ptr<IContentPipeline>& pipe);
        void load();
        void unload();

       private:
        void collect(const std::string& dir);
        std::string rootDir;
        std::vector<std::string> files;
        std::vector<std::shared_ptr<IContentPipeline> > pipes;
};
}  // namespace mygame
#endif