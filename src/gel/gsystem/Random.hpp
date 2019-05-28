#ifndef GEL_GSYSTEM_RANDOM_HPP
#define GEL_GSYSTEM_RANDOM_HPP
namespace gel {
class Random {
       public:
        explicit Random();
        int generate(int min, int max) const;
        float generate(float min, float max) const;

       private:
};
}  // namespace gel
#endif