#include "RemoveFromAggroTableValue.h"
#include "FindAggroTableSlotByEntityId.h"
#include "RefreshAggroTableMax.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../utils/pool/PoolFree.h"

void removeFromAggroTableValue(Context &ctx, uint32_t n, int entityId)
{
    auto &aggroTable = ctx.data.npc.aggroTable;
    int slot = findAggroTableSlotByEntityId(ctx, n, entityId);

    if (slot == INVALID_ID)
        return;

    const bool removedMaxEntity = aggroTable.maxEntityId[n] == entityId;
    aggroTable.value[n][slot] = 0.0f;
    aggroTable.entityId[n][slot] = INVALID_ID;
    poolFree(aggroTable.pool, n, slot);

    if (removedMaxEntity)
        refreshAggroTableMax(ctx, n);
}
