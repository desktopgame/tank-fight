#include "HitCache.hpp"
HitCache::HitCache( std::shared_ptr<Actor> actor,  gel::AABB aabb)
    : actor(actor), aabb(aabb) {}