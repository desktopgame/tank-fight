#ifndef GEL_GSYSTEM_NUMBER_HPP
#define GEL_GSYSTEM_NUMBER_HPP
#include <array>
#include <functional>
#include "../model/Vector2.hpp"
namespace gel {
class TextureManager;
/**
 * Number is class of draw for number.
 */
class Number {
       public:
        /**
         * @param drawFn
         */
        explicit Number(std::function<void(Vector2, int)> drawFn);
        /**
         * @param textureManager
         * @param files
         */
        explicit Number(const std::shared_ptr<TextureManager>& textureManager,
                        const std::array<std::string, 10>& files);
        /**
         * @param i
         */
        void draw(int i);
        Vector2 position;

       private:
        std::function<void(Vector2, int)> drawFn;
};
}  // namespace gel
#endif