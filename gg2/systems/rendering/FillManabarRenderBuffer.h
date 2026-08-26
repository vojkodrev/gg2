#pragma once
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/ui/Manabar.h"
#include <cstdint>

template<int N>
inline void fillManabarRenderBuffer(
    RenderBuffer &rb,
    const Manabar<N> &manabar,
    uint32_t entityIndex,
    uint32_t groupId)
{
    if (!manabar.show[entityIndex])
        return;

    fillEntityBaseRenderBuffer(
        rb,
        manabar.base,
        entityIndex,
        groupId,
        manabar.zIndex[entityIndex]);
}
