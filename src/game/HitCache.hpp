#ifndef GAME_HITCACHE_HPP
#define GAME_HITCACHE_HPP
#include <memory>
#include "../gel/gel.hpp"
#include "Actor.hpp"
class HitCache {
       public:
        HitCache( std::shared_ptr<Actor> actor, gel::AABB aabb);
        std::shared_ptr<Actor> actor;
        gel::AABB aabb;
};
#endif