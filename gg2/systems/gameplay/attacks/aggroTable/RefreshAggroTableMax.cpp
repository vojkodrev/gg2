#include "RefreshAggroTableMax.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"

void refreshAggroTableMax(Context &ctx, uint32_t n)
{
    auto &aggroTable = ctx.data.npc.aggroTable;
    float maxValue = 0.0f;
    int maxEntityId = INVALID_ID;

    for (uint32_t i = 0; i < aggroTable.pool.count[n]; i++)
    {
        if (!aggroTable.pool.active[n][i])
            continue;

        if (maxEntityId != INVALID_ID && aggroTable.value[n][i] <= maxValue)
            continue;

        maxValue = aggroTable.value[n][i];
        maxEntityId = aggroTable.entityId[n][i];
    }

    aggroTable.maxValue[n] = maxValue;
    aggroTable.maxEntityId[n] = maxEntityId;
}
