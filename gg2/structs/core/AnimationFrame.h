#pragma once
#include <cstdint>
#include "AnimationConstants.h"
#include "SpriteSrc.h"
#include "Anchor.h"

template<int N>
struct AnimationFrame
{
    SpriteSrc<N, MAX_ANIMATION_FRAMES> src;
    Anchor<N, MAX_ANIMATION_FRAMES> anchor;
    Anchor<N, MAX_ANIMATION_FRAMES> collision;
    uint32_t frameDuration[N][MAX_ANIMATION_FRAMES];
};
