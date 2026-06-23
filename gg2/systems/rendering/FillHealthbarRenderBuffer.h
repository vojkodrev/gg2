#pragma once
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"
#include "../../structs/ui/Healthbar.h"
#include <cstdint>

template<int N>
inline void fillHealthbarRenderBuffer(
    RenderBuffer &rb,
    const Healthbar<N> &healthbar,
    uint32_t entityIndex,
    uint32_t groupId)
{
    if (!healthbar.show[entityIndex])
        return;

    fillEntityBaseRenderBuffer(
        rb,
        healthbar.base,
        entityIndex,
        groupId,
        HEALTHBAR_Z_INDEX);
}
