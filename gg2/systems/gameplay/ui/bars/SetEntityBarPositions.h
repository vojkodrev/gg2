#pragma once
#include "SetBarPosition.h"
#include "../../../structs/entity/EntityBase.h"
#include "../../../structs/core/constants/HealthbarConstants.h"
#include "../../../structs/statistics/Statistics.h"
#include "../../../structs/ui/Healthbar.h"
#include "../../../structs/ui/Manabar.h"
#include <cstdint>

template<int N>
inline void setEntityBarPositions(
    Healthbar<N> &healthbar,
    Manabar<N> &manabar,
    const EntityBase<N> &entityBase,
    const Statistics<N> &statistics,
    uint32_t index)
{
    const bool hasMana = statistics.mana.maxMana[index] > 0;
    if (healthbar.show[index] &&
        (entityBase.position.dirty[index] ||
         healthbar.dirty[index] ||
         statistics.health.dirty[index]))
        setBarPosition(
            healthbar.base,
            entityBase,
            hasMana ? HEALTHBAR_Y_OFFSET : 0.0f,
            index);

    if (hasMana &&
        manabar.show[index] &&
        (entityBase.position.dirty[index] ||
         manabar.dirty[index] ||
         statistics.mana.dirty[index]))
        setBarPosition(manabar.base, entityBase, MANABAR_Y_OFFSET, index);
}
