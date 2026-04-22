#include "UpdateMonster.h"
#include "DistToPlayer.h"
#include "DistToSpawn.h"
#include "IsNearColEdge.h"
#include "MoveColCenterToward.h"
#include "RandomIdleTimer.h"
#include "EntityAABB.h"
#include "constants.h"

void UpdateMonster(uint32_t n, Context &ctx)
{
    float dt = ctx.frame.dt;
    auto &npc = ctx.data.npc;
    auto &ai = npc.ai;
    auto &player = ctx.data.player;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:
        ai.idleTimer[n] -= dt;
        if (DistToPlayer(ctx, n) < NPC_DETECT_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToPlayer;
        }
        else if (ai.idleTimer[n] <= 0.0f)
        {
            ai.state[n] = NPCAiState::Patrolling;
        }
        break;

    case NPCAiState::Patrolling:
    {
        if (DistToPlayer(ctx, n) < NPC_DETECT_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToPlayer;
            break;
        }
        if (ai.patrolCount[n] == 0)
            break;
        uint32_t p = ai.patrolIndex[n];
        float tx = ai.spawn.x[n] + ai.patrol.x[n][p];
        float ty = ai.spawn.y[n] + ai.patrol.y[n][p];
        MoveColCenterToward(ctx, n, tx, ty, NPC_MONSTER_SPEED);
        if (IsNearColEdge(ctx, n, tx, ty))
        {
            ai.patrolIndex[n] = (p + 1) % ai.patrolCount[n];
            if ((rand() % 100) + 1 <= 10)
            {
                ai.state[n] = NPCAiState::Idle;
                ai.idleTimer[n] = RandomIdleTimer();
            }
        }
        break;
    }

    case NPCAiState::GoToPlayer:
    {
        if (DistToSpawn(ctx, n) > NPC_LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        SDL_FPoint playerColCenter = EntityColCenter(EntityColAABB(ctx.data.player));
        MoveColCenterToward(ctx, n, playerColCenter.x, playerColCenter.y, NPC_MONSTER_SPEED);
        if (IsNearColEdge(ctx, n, playerColCenter.x, playerColCenter.y, NPC_ATTACK_REACH))
            ai.state[n] = NPCAiState::Attack;
        break;
    }

    case NPCAiState::Attack:
    {
        if (DistToSpawn(ctx, n) > NPC_LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        SDL_FPoint playerColCenter = EntityColCenter(EntityColAABB(ctx.data.player));
        if (!IsNearColEdge(ctx, n, playerColCenter.x, playerColCenter.y, NPC_ATTACK_REACH))
            ai.state[n] = NPCAiState::GoToPlayer;
        break;
    }

    case NPCAiState::GoToSpawn:
        MoveColCenterToward(ctx, n, ai.spawn.x[n], ai.spawn.y[n], NPC_MONSTER_SPEED);
        if (IsNearColEdge(ctx, n, ai.spawn.x[n], ai.spawn.y[n]))
        {
            ai.idleTimer[n] = RandomIdleTimer();
            ai.state[n] = NPCAiState::Idle;
        }
        break;
    }
}
