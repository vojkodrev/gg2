#pragma once
#include <cstdint>
#include "AnimationConstants.h"
#include "SpriteSrc.h"
#include "Anchor.h"

template<int NEntities>
struct AnimationFrame
{
    SpriteSrc<NEntities, MAX_ANIMATION_FRAMES> src;
    Anchor<NEntities, MAX_ANIMATION_FRAMES, 1> anchor;
    Anchor<NEntities, MAX_ANIMATION_FRAMES, MAX_FRAME_COLLISIONS> collision;
    uint32_t frameDuration[NEntities][MAX_ANIMATION_FRAMES];
};
