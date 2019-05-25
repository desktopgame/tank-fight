#ifndef APP_CONTENT_CONTENTMANAGER_HPP
#define APP_CONTENT_CONTENTMANAGER_HPP
#include <memory>
#include <string>
#include <vector>

namespace mygame {
class IContentPipeline;
/**
 * ContentManager is list of ContentPipeline.
 */
class ContentManager {
       public:
        ContentManager(const std::string& rootDir);
        /**
         * add pipeline.
         * @param pipe
         */
        void add(const std::shared_ptr<IContentPipeline>& pipe);
        /**
         * remove pipeline.
         * @param pipe
         */
        void remove(const std::shared_ptr<IContentPipeline>& pipe);

        /**
         * load a all asset.
         */
        void load();
        /**
         * unload a all asset.
         */
        void unload();

       private:
        void collect(const std::string& dir);
        std::string rootDir;
        std::vector<std::string> files;
        std::vector<std::shared_ptr<IContentPipeline> > pipes;
};
}  // namespace mygame
#endif