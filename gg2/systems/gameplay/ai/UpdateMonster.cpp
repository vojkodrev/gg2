#include "UpdateMonster.h"
#include <atomic>
#include "DistToPlayer.h"
#include "DistToSpawn.h"
#include "HasReachedRect.h"
#include "AreColBoxesNear.h"
#include "EntityAABB.h"
#include "CenteredRect.h"
#include "Constants.h"
#include "UpdateAStarPath.h"
#include "SetNpcAiStateGoToPlayer.h"
#include "SetNpcAiStateGoToSpawn.h"
#include "SetNpcAiStateAttack.h"
#include "SetNpcAiStatePatrolling.h"
#include "SetNpcAiStateIdle.h"

void updateMonster(uint32_t n, Context &ctx)
{
    float dt = ctx.frame.dt;
    auto &npc = ctx.data.npc;
    auto &ai = npc.ai;
    auto &player = ctx.data.player;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:
        ai.idleTimer[n] -= dt;
        if (distToPlayer(ctx, n) < NPC_DETECT_RADIUS)
        {
            setNpcAiStateGoToPlayer(n, ctx);
        }
        else if (ai.idleTimer[n] <= 0.0f)
        {
            setNpcAiStatePatrolling(n, ctx);
        }
        break;

    case NPCAiState::Patrolling:
    {
        if (distToPlayer(ctx, n) < NPC_DETECT_RADIUS)
        {
            setNpcAiStateGoToPlayer(n, ctx);
            break;
        }
        if (ai.patrolCount[n] == 0)
            break;
        uint32_t p = ai.patrolIndex[n];
        SDL_FPoint patrolPt = { ai.spawn.x[n] + ai.patrol.x[n][p], ai.spawn.y[n] + ai.patrol.y[n][p] };
        SDL_FRect patrolCol = centeredRect(patrolPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
        updateAStarPath(n, ctx, patrolCol);
        if (hasReachedRect(ctx, n, patrolCol))
        {
            ai.patrolIndex[n] = (p + 1) % ai.patrolCount[n];
            if ((rand() % 100) + 1 <= 10)
            {
                setNpcAiStateIdle(n, ctx);
            }
        }
        break;
    }

    case NPCAiState::GoToPlayer:
    {
        if (distToSpawn(ctx, n) > NPC_LEASH_RADIUS)
        {
            setNpcAiStateGoToSpawn(n, ctx);
            break;
        }

        SDL_FRect playerCol = entityColAABB(ctx.data.player);

        if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
        {
            setNpcAiStateAttack(n, ctx);
            break;
        }

        updateAStarPath(n, ctx, playerCol);
        break;
    }

    case NPCAiState::Attack:
    {
        if (distToSpawn(ctx, n) > NPC_LEASH_RADIUS)
        {
            setNpcAiStateGoToSpawn(n, ctx);
            break;
        }
        SDL_FRect playerCol = entityColAABB(ctx.data.player);
        if (!areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
            setNpcAiStateGoToPlayer(n, ctx);
        break;
    }

    case NPCAiState::GoToSpawn:
    {
        SDL_FPoint spawnPt = { ai.spawn.x[n], ai.spawn.y[n] };
        SDL_FRect spawnCol = centeredRect(spawnPt, (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP);
        updateAStarPath(n, ctx, spawnCol);
        if (hasReachedRect(ctx, n, spawnCol))
            setNpcAiStateIdle(n, ctx);
        break;
    }
    }
}
