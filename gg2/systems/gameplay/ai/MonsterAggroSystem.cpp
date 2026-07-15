#include "MonsterAggroSystem.h"
#include "SetNpcAiStatePursueTarget.h"
#include "monster/RefreshNpcAttackedTimer.h"
#include "../../../structs/npc/NPCAiState.h"
#include "../../../structs/npc/NPCAiType.h"

void monsterAggroSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;

    for (uint32_t npcId = 0; npcId < MAX_NPCS; npcId++)
    {
        if (!npc.active[npcId])
            continue;

        if (npc.ai.type[npcId] != NPCAiType::Monster)
            continue;

        const NPCAiState state = npc.ai.state[npcId];
        if (state != NPCAiState::Idle && state != NPCAiState::Patrolling)
            continue;

        if (npc.aggroTable.pool.count[npcId] == 0)
            continue;

        refreshNpcAttackedTimer(npcId, ctx);
        setNpcAiStatePursueTarget(npcId, ctx);
    }
}
