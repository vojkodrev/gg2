#include "AddToAggroTableValue.h"
#include "FindAggroTableSlotByEntityId.h"
#include "RefreshAggroTableMax.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/pool/PoolAlloc.h"

void addToAggroTableValue(Context &ctx, uint32_t n, int entityId, float value)
{
    auto &aggroTable = ctx.data.npc.aggroTable;
    int slot = findAggroTableSlotByEntityId(ctx, n, entityId);

    if (slot == INVALID_ID)
    {
        slot = poolAlloc(aggroTable.pool, n);
        if (slot == INVALID_ID)
            return;

        aggroTable.entityId[n][slot] = entityId;
    }

    const bool replacedMaxEntity = aggroTable.maxEntityId[n] == entityId;
    aggroTable.value[n][slot] += value;
    const float nextValue = aggroTable.value[n][slot];

    if (aggroTable.maxEntityId[n] == INVALID_ID || nextValue >= aggroTable.maxValue[n])
    {
        aggroTable.maxValue[n] = nextValue;
        aggroTable.maxEntityId[n] = entityId;
        return;
    }

    if (replacedMaxEntity)
        refreshAggroTableMax(ctx, n);
}
