#include "Random.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
namespace gel {
Random::Random() { ::srand(::time(NULL)); }

int Random::generate(int min, int max) const {
        // https://stackoverflow.com/questions/1202687/how-do-i-get-a-specific-range-of-numbers-from-rand
        return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}
float Random::generate(float min, float max) const {
        float scale = rand() / (float)RAND_MAX;
        return min + scale * (max - min);
}
}  // namespace gel