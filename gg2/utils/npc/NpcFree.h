#pragma once
#include "../../structs/core/Group.h"
#include "../../structs/npc/NPC.h"
#include "../groups/GroupFree.h"
#include "../pool/PoolFree.h"

template<uint32_t TGroupCapacity>
inline void npcFree(NPC &npc, Group<TGroupCapacity> &groups, int npcIndex)
{
    groupFree(groups, npc.groupId[npcIndex]);
    poolFree(npc.pool, npcIndex);
}
