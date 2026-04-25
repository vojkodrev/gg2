#include "UpdateMonster.h"
#include "DistToPlayer.h"
#include "DistToSpawn.h"
#include "IsNearColEdge.h"
#include "MoveColCenterToward.h"
#include "RandomIdleTimer.h"
#include "EntityAABB.h"
#include "Constants.h"

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
        SDL_FRect npcCol = entityColAABB(ctx.data.npc, n);
        SDL_FPoint target = {tx, ty};
        if (SDL_PointInRectFloat(&target, &npcCol))
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
        SDL_FPoint playerColCenter = entityColCenter(playerCol);
        moveColCenterToward(ctx, n, playerColCenter.x, playerColCenter.y, NPC_MONSTER_SPEED);
        SDL_FRect playerColExpanded = {playerCol.x - NPC_ATTACK_REACH, playerCol.y - NPC_ATTACK_REACH,
                                       playerCol.w + NPC_ATTACK_REACH * 2, playerCol.h + NPC_ATTACK_REACH * 2};
        SDL_FRect npcCol = entityColAABB(ctx.data.npc, n);
        if (SDL_HasRectIntersectionFloat(&npcCol, &playerColExpanded))
            ai.state[n] = NPCAiState::Attack;
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
        SDL_FRect playerColExpanded = {playerCol.x - NPC_ATTACK_REACH, playerCol.y - NPC_ATTACK_REACH,
                                       playerCol.w + NPC_ATTACK_REACH * 2, playerCol.h + NPC_ATTACK_REACH * 2};
        SDL_FRect npcCol = entityColAABB(ctx.data.npc, n);
        if (!SDL_HasRectIntersectionFloat(&npcCol, &playerColExpanded))
            ai.state[n] = NPCAiState::GoToPlayer;
        break;
    }

    case NPCAiState::GoToSpawn:
        moveColCenterToward(ctx, n, ai.spawn.x[n], ai.spawn.y[n], NPC_MONSTER_SPEED);
        if (isNearColEdge(ctx, n, ai.spawn.x[n], ai.spawn.y[n]))
        {
            ai.idleTimer[n] = randomIdleTimer();
            ai.state[n] = NPCAiState::Idle;
        }
        break;
    }
}
