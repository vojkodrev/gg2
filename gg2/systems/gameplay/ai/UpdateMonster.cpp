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
            ai.state[n] = NPCAiState::GoToPlayer;
        }
        else if (ai.idleTimer[n] <= 0.0f)
        {
            ai.state[n] = NPCAiState::Patrolling;
        }
        break;

    case NPCAiState::Patrolling:
    {
        if (distToPlayer(ctx, n) < NPC_DETECT_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToPlayer;
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
                ai.state[n] = NPCAiState::Idle;
                ai.idleTimer[n] = randomIdleTimer();
            }
        }
        break;
    }

    case NPCAiState::GoToPlayer:
    {
        if (distToSpawn(ctx, n) > NPC_LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }

        SDL_FRect playerCol = entityColAABB(ctx.data.player);

        if (areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
        {
            ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
            ai.state[n] = NPCAiState::Attack;
            break;
        }

        // acquire: pairs with release store in RequestAStarPath, ensures path data is visible
        auto pathStatus = ai.pathStatus[n].load(std::memory_order_acquire);

        if (pathStatus == NPCPathStatus::IDLE ||
            pathStatus == NPCPathStatus::CALCULATION_FAILED)
        {
            SDL_FPoint npcPos = { npc.position.x[n], npc.position.y[n] };
            requestAStarPath(ctx, n, npcPos, playerCol, NPC_MONSTER_PATH_STEP);
        }
        else if (pathStatus == NPCPathStatus::CALCULATION_FINISHED)
        {
            uint32_t i = ai.pathIndex[n];
            float tx = (float)ai.path.x[n][i];
            float ty = (float)ai.path.y[n][i];
            moveColCenterToward(ctx, n, tx, ty, NPC_MONSTER_SPEED);
            if (hasReachedPoint(ctx, n, tx, ty))
            {
                if (i + 1 < ai.pathLength[n])
                    ai.pathIndex[n]++;
                else
                    ai.pathStatus[n].store(NPCPathStatus::IDLE, std::memory_order_relaxed);
            }
        }
        break;
    }

    case NPCAiState::Attack:
    {
        if (distToSpawn(ctx, n) > NPC_LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        SDL_FRect playerCol = entityColAABB(ctx.data.player);
        if (!areColBoxesNear(ctx, n, playerCol, NPC_ATTACK_REACH))
            ai.state[n] = NPCAiState::GoToPlayer;
        break;
    }

    case NPCAiState::GoToSpawn:
        moveColCenterToward(ctx, n, ai.spawn.x[n], ai.spawn.y[n], NPC_MONSTER_SPEED);
        if (hasReachedPoint(ctx, n, ai.spawn.x[n], ai.spawn.y[n]))
        {
            ai.idleTimer[n] = randomIdleTimer();
            ai.state[n] = NPCAiState::Idle;
        }
        break;
    }
}
