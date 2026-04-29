#include "UpdateMonster.h"
#include <atomic>
#include "DistToPlayer.h"
#include "DistToSpawn.h"
#include "HasReachedPoint.h"
#include "AreColBoxesNear.h"
#include "MoveColCenterToward.h"
#include "RandomIdleTimer.h"
#include "EntityAABB.h"
#include "Constants.h"
#include "UpdateAStarPath.h"

static void setNpcAiStateGoToPlayer(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::GoToPlayer;
}

static void setNpcAiStateGoToSpawn(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::GoToSpawn;
}

static void setNpcAiStateAttack(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::Attack;
}

static void setNpcAiStatePatrolling(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.state[n] = NPCAiState::Patrolling;
}

static void setNpcAiStateIdle(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
    ctx.data.npc.ai.idleTimer[n] = randomIdleTimer();
    ctx.data.npc.ai.state[n] = NPCAiState::Idle;
}

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
        float tx = ai.spawn.x[n] + ai.patrol.x[n][p];
        float ty = ai.spawn.y[n] + ai.patrol.y[n][p];
        moveColCenterToward(ctx, n, tx, ty, NPC_MONSTER_SPEED);
        if (hasReachedPoint(ctx, n, tx, ty))
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
        float spawnX = ai.spawn.x[n], spawnY = ai.spawn.y[n];
        SDL_FRect spawnCol = { spawnX - NPC_MONSTER_PATH_STEP * 0.5f, spawnY - NPC_MONSTER_PATH_STEP * 0.5f,
                               (float)NPC_MONSTER_PATH_STEP, (float)NPC_MONSTER_PATH_STEP };
        updateAStarPath(n, ctx, spawnCol);
        if (hasReachedPoint(ctx, n, spawnX, spawnY))
            setNpcAiStateIdle(n, ctx);
        break;
    }
    }
}
