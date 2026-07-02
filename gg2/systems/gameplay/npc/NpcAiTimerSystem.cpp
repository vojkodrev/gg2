#include "NpcAiTimerSystem.h"
#include <algorithm>

void npcAiTimerSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &npc = ctx.data.npc;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;

        npc.ai.idleTimer[i] = std::max(0.0f, npc.ai.idleTimer[i] - dt);
        npc.ai.repathTimer[i] = std::max(0.0f, npc.ai.repathTimer[i] - dt);
    }
}
