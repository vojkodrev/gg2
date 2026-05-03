#pragma once
#include <cstdint>
#include "Constants.h"
#include "SpriteSrc.h"
#include "EntityCollision.h"

template<int N>
struct AnimationFrame
{
    SpriteSrc<N, MAX_ANIMATION_FRAMES> src;
    EntityCollision<N, MAX_ANIMATION_FRAMES> collision;
    uint32_t frameDuration[N][MAX_ANIMATION_FRAMES];
};
