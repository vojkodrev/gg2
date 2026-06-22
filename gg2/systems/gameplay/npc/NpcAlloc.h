#pragma once
#include "../../../structs/core/Group.h"
#include "../../../structs/npc/NPC.h"
#include "../../../utils/groups/GroupAlloc.h"
#include "../../../utils/pool/PoolAlloc.h"
#include "../../../utils/pool/PoolFree.h"

template<uint32_t TGroupCapacity>
inline int npcAlloc(NPC &npc, Group<TGroupCapacity> &groups)
{
    int npcIndex = poolAlloc(npc.pool);
    if (npcIndex == -1)
        return -1;

    int groupId = groupAlloc(groups);
    if (groupId == -1)
    {
        poolFree(npc.pool, npcIndex);
        return -1;
    }

    npc.groupId[npcIndex] = groupId;
    return npcIndex;
}
