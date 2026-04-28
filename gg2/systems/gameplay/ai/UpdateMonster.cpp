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
#include "astar/RequestAStarPath.h"

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

        // acquire: pairs with release store in RequestAStarPath, ensures path data is visible
        auto pathStatus = ai.pathStatus[n].load(std::memory_order_acquire);

        if (pathStatus == NPCPathStatus::IDLE ||
            pathStatus == NPCPathStatus::CALCULATION_FAILED)
        {
            requestAStarPath(ctx, n, entityColAABB(npc, n), playerCol, NPC_MONSTER_PATH_STEP);
        }
        else if (pathStatus == NPCPathStatus::CALCULATION_FINISHED)
        {
            SDL_FPoint npcCenter = entityColCenter(entityColAABB(npc, n));
            float r = NPC_MONSTER_SPEED * dt;
            uint32_t len = ai.pathLength[n];
            uint32_t i = ai.pathIndex[n];

            // skip ahead to the furthest path point reachable this frame
            for (uint32_t j = i + 1; j < len; j++)
            {
                float dx = (float)ai.path.x[n][j] - npcCenter.x;
                float dy = (float)ai.path.y[n][j] - npcCenter.y;
                if (dx * dx + dy * dy <= r * r)
                    i = j;
                else
                    break;
            }
            ai.pathIndex[n] = i;

            float tx = (float)ai.path.x[n][i];
            float ty = (float)ai.path.y[n][i];
            moveColCenterToward(ctx, n, tx, ty, NPC_MONSTER_SPEED);

            if (i + 1 >= len && hasReachedPoint(ctx, n, tx, ty))
                ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
        }
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
        moveColCenterToward(ctx, n, ai.spawn.x[n], ai.spawn.y[n], NPC_MONSTER_SPEED);
        if (hasReachedPoint(ctx, n, ai.spawn.x[n], ai.spawn.y[n]))
        {
            setNpcAiStateIdle(n, ctx);
        }
        break;
    }
}
