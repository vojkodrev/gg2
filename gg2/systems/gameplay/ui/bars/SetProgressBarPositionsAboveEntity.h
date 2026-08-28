#pragma once
#include "SetProgressBarPositionAboveEntity.h"
#include "../../../structs/entity/EntityBase.h"
#include "../../../structs/core/constants/HealthbarConstants.h"
#include "../../../structs/statistics/Statistics.h"
#include "../../../structs/ui/ProgressBar.h"
#include <cstdint>

template<int N>
inline void setProgressBarPositionsAboveEntity(
    ProgressBar<N> &healthbar,
    ProgressBar<N> &manabar,
    const EntityBase<N> &entityBase,
    const Statistics<N> &statistics,
    uint32_t index)
{
    const bool hasMana = statistics.mana.maxMana[index] > 0;
    if (healthbar.show[index] &&
        (entityBase.position.dirty[index] ||
         healthbar.dirty[index] ||
         statistics.health.dirty[index]))
        setProgressBarPositionAboveEntity(
            healthbar.base,
            entityBase,
            hasMana ? HEALTHBAR_Y_OFFSET : 0.0f,
            index);

    if (hasMana &&
        manabar.show[index] &&
        (entityBase.position.dirty[index] ||
         manabar.dirty[index] ||
         statistics.mana.dirty[index]))
        setProgressBarPositionAboveEntity(
            manabar.base,
            entityBase,
            MANABAR_Y_OFFSET,
            index);
}
