#pragma once
#include "../../../structs/core/Group.h"
#include "../../../structs/npc/NPC.h"
#include "../../../utils/groups/GroupAlloc.h"

template<uint32_t TGroupCapacity>
inline int npcAlloc(NPC &npc, Group<TGroupCapacity> &groups)
{
    int npcIndex = -1;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (npc.active[i])
            continue;

        npcIndex = (int)i;
        npc.active[i] = true;
        break;
    }

    if (npcIndex == -1)
        return -1;

    int groupId = groupAlloc(groups);
    if (groupId == -1)
    {
        npc.active[npcIndex] = false;
        return -1;
    }

    npc.groupId[npcIndex] = groupId;
    return npcIndex;
}
