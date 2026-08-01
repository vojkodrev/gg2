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

        npc.ai.attackedTimer[i] = std::max(0.0f, npc.ai.attackedTimer[i] - dt);
        npc.ai.idleTimer[i] = std::max(0.0f, npc.ai.idleTimer[i] - dt);
        npc.ai.repathTimer[i] = std::max(0.0f, npc.ai.repathTimer[i] - dt);
        npc.ai.pursueTargetRangeCheckTimer[i] = std::max(
            0.0f,
            npc.ai.pursueTargetRangeCheckTimer[i] - dt);
        npc.ai.rangedAttackTargetTooCloseCheckTimer[i] = std::max(
            0.0f,
            npc.ai.rangedAttackTargetTooCloseCheckTimer[i] - dt);
        npc.ai.rangedRetreatPointCheckTimer[i] = std::max(
            0.0f,
            npc.ai.rangedRetreatPointCheckTimer[i] - dt);
        npc.ai.rangedAttackStaggerTimer[i] = std::max(
            0.0f,
            npc.ai.rangedAttackStaggerTimer[i] - dt);
        npc.ai.targetVisibleTimer[i] = std::max(
            0.0f,
            npc.ai.targetVisibleTimer[i] - dt);
        npc.ai.pathTargetCheckTimer[i] = std::max(
            0.0f,
            npc.ai.pathTargetCheckTimer[i] - dt);
        npc.ai.flipTimer[i] = std::max(
            0.0f,
            npc.ai.flipTimer[i] - dt);
    }
}
