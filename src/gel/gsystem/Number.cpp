#include "Number.hpp"
#include "../device/Graphics.hpp"
#include "../device/TextureManager.hpp"
namespace gel {
Number::Number(std::function<void(Vector2, int)> drawFn) : position(0,0), drawFn(drawFn) {}
Number::Number(const std::shared_ptr<TextureManager>& textureManager,
               const std::array<std::string, 10>& files) {
        this->drawFn = [textureManager, files](Vector2 pos, int i) {
                auto tex = textureManager->getTexture(files[i]);
                drawTexture(pos, Color4::white(1), tex);
        };
}
void Number::draw(int i) { drawFn(position, i); }
}  // namespace gel