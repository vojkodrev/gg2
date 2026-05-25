#pragma once
#include <cstdint>

template<typename EntityData>
inline void loadEmptyEntityBase(EntityData &entityData, uint32_t parentEntityIdx)
{
    entityData.animation.animationType[parentEntityIdx] = AnimationType::None;
    entityData.animation.frameCount[parentEntityIdx] = 0;
}
