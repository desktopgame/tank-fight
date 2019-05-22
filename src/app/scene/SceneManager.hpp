#ifndef APP_SCENE_SCENEMANAGER_HPP
#define APP_SCENE_SCENEMANAGER_HPP
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>

namespace mygame {
class IScene;
class SceneManager {
       public:
        SceneManager();
        void put(const std::string& name, const std::shared_ptr<IScene>& scene);
        void remove(const std::string& name);
        void bind(const std::string& name);
        void update();
        void draw();
        std::optional<std::shared_ptr<IScene> > getScene();

       private:
        std::string mCurrent;
        std::unordered_map<std::string, std::shared_ptr<IScene> > mSceneMap;
};
}  // namespace mygame
#endif