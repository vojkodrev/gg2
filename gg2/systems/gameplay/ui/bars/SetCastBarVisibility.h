#pragma once
#include "../../../structs/ui/CastBar.h"
#include <cstdint>

template<int N>
inline void setCastBarVisibility(CastBar<N> &castBar, uint32_t index)
{
    auto &progressBar = castBar.progressBar;
    if (!progressBar.dirty[index])
        return;

    progressBar.show[index] = castBar.timer[index] > 0.0f;
}
