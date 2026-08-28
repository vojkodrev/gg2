#pragma once
#include "FillEntityBaseRenderBuffer.h"
#include "../../structs/ui/ProgressBar.h"
#include <cstdint>

template<int N>
inline void fillProgressBarRenderBuffer(
    RenderBuffer &renderBuffer,
    const ProgressBar<N> &progressBar,
    uint32_t entityIndex,
    uint32_t groupId)
{
    if (!progressBar.show[entityIndex])
        return;

    fillEntityBaseRenderBuffer(
        renderBuffer,
        progressBar.base,
        entityIndex,
        groupId,
        progressBar.zIndex[entityIndex]);
}
