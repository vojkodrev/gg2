#include "FindAggroTableSlotByEntityId.h"
#include "../../../../structs/core/constants/IndexConstants.h"

int findAggroTableSlotByEntityId(Context &ctx, uint32_t n, int entityId)
{
    auto &aggroTable = ctx.data.npc.aggroTable;

    for (uint32_t i = 0; i < aggroTable.pool.count[n]; i++)
    {
        if (!aggroTable.pool.active[n][i])
            continue;

        if (aggroTable.entityId[n][i] != entityId)
            continue;

        return (int)i;
    }

    return INVALID_ID;
}
