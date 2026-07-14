#include "SetAggroTableValue.h"
#include "SortAggroTable.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"

void setAggroTableValue(Context &ctx, uint32_t n, int entityId, float value)
{
    auto &aggroTable = ctx.data.npc.aggroTable;
    uint32_t &count = aggroTable.count[n];
    int slot = INVALID_ID;

    for (uint32_t i = 0; i < count; i++)
    {
        if (aggroTable.entityId[n][i] != entityId)
            continue;

        slot = (int)i;
        break;
    }

    if (slot == INVALID_ID)
    {
        if (count >= MAX_AGGRO_SLOTS)
            return;

        slot = (int)count;
        aggroTable.entityId[n][slot] = entityId;
        count++;
    }

    aggroTable.value[n][slot] = value;
    sortAggroTable(ctx, n);
}
