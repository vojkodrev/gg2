#pragma once
#include "SetProgressBarFrame.h"
#include "../../../structs/ui/CastBar.h"
#include <cstdint>

template<int N>
inline void setCastBarFrame(CastBar<N> &castBar, uint32_t index)
{
    auto &progressBar = castBar.progressBar;
    if (!progressBar.dirty[index])
        return;

    setProgressBarFrame(
        progressBar,
        castBar.duration[index] - castBar.timer[index],
        castBar.duration[index],
        index);
}
