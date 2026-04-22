#include "NPCAiSystem.h"
#include "EntityAABB.h"
#include "RandomIdleTimer.h"
#include <cmath>

static constexpr float MONSTER_SPEED       = 100.0f;
static constexpr float DETECT_RADIUS       = 200.0f;
static constexpr float ATTACK_REACH        = 40.0f;
static constexpr float LEASH_RADIUS        = 400.0f;

static float dist(float ax, float ay, float bx, float by)
{
    float dx = ax - bx;
    float dy = ay - by;
    return sqrtf(dx * dx + dy * dy);
}

static float distToPlayer(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter    = entityColCenter(entityColAABB(ctx.data.npc, n));
    SDL_FPoint playerColCenter = entityColCenter(entityColAABB(ctx.data.player));
    return dist(npcColCenter.x, npcColCenter.y, playerColCenter.x, playerColCenter.y);
}

static float distToSpawn(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter = entityColCenter(entityColAABB(ctx.data.npc, n));
    return dist(npcColCenter.x, npcColCenter.y, ctx.data.npc.ai.spawn.x[n], ctx.data.npc.ai.spawn.y[n]);
}

static bool isNearColEdge(Context &ctx, uint32_t n, float tx, float ty, float buffer = 0.0f)
{
    SDL_FRect col = entityColAABB(ctx.data.npc, n);
    SDL_FPoint colCenter = entityColCenter(col);
    float nearReach = SDL_min(col.w, col.h) * 0.5f + buffer;
    return dist(colCenter.x, colCenter.y, tx, ty) < nearReach;
}

static void moveColCenterToward(Context &ctx, uint32_t n, float tx, float ty, float speed)
{
    auto &npc = ctx.data.npc;
    float dt = ctx.frame.dt;
    SDL_FRect col = entityColAABB(npc, n);
    SDL_FPoint colCenter = entityColCenter(col);
    float dx = tx - colCenter.x;
    float dy = ty - colCenter.y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;
    npc.position.x[n] += dx / d * speed * dt;
    npc.position.y[n] += dy / d * speed * dt;
}

static void updateMonster(uint32_t n, Context &ctx)
{
    float dt = ctx.frame.dt;
    auto &npc = ctx.data.npc;
    auto &ai = npc.ai;
    auto &player = ctx.data.player;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:
        ai.idleTimer[n] -= dt;
        if (distToPlayer(ctx, n) < DETECT_RADIUS)
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
        if (distToPlayer(ctx, n) < DETECT_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToPlayer;
            break;
        }
        if (ai.patrolCount[n] == 0)
            break;
        uint32_t p = ai.patrolIndex[n];
        float tx = ai.spawn.x[n] + ai.patrol.x[n][p];
        float ty = ai.spawn.y[n] + ai.patrol.y[n][p];
        moveColCenterToward(ctx, n, tx, ty, MONSTER_SPEED);
        if (isNearColEdge(ctx, n, tx, ty))
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
        if (distToSpawn(ctx, n) > LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        SDL_FPoint playerColCenter = entityColCenter(entityColAABB(ctx.data.player));
        moveColCenterToward(ctx, n, playerColCenter.x, playerColCenter.y, MONSTER_SPEED);
        if (isNearColEdge(ctx, n, playerColCenter.x, playerColCenter.y, ATTACK_REACH))
            ai.state[n] = NPCAiState::Attack;
        break;
    }

    case NPCAiState::Attack:
    {
        if (distToSpawn(ctx, n) > LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        SDL_FPoint playerColCenter = entityColCenter(entityColAABB(ctx.data.player));
        if (!isNearColEdge(ctx, n, playerColCenter.x, playerColCenter.y, ATTACK_REACH))
            ai.state[n] = NPCAiState::GoToPlayer;
        break;
    }

    case NPCAiState::GoToSpawn:
        moveColCenterToward(ctx, n, ai.spawn.x[n], ai.spawn.y[n], MONSTER_SPEED);
        if (isNearColEdge(ctx, n, ai.spawn.x[n], ai.spawn.y[n]))
        {
            ai.idleTimer[n] = RandomIdleTimer();
            ai.state[n] = NPCAiState::Idle;
        }
        break;
    }
}

void NPCAiSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;

    for (uint32_t n = 0; n < npc.npcCount; n++)
    {
        if (npc.ai.type[n] == NPCAiType::Monster)
            updateMonster(n, ctx);
    }
}
