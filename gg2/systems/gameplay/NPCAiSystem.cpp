#include "NPCAiSystem.h"
#include "EntityAABB.h"
#include "RandomIdleTimer.h"
#include <cmath>

static constexpr float MONSTER_SPEED       = 100.0f;
static constexpr float DETECT_RADIUS       = 200.0f;
static constexpr float ATTACK_REACH        = 20.0f;
static constexpr float LEASH_RADIUS        = 400.0f;
static constexpr float NEAR_POINT_BUFFER   = 8.0f;

static float dist(float ax, float ay, float bx, float by)
{
    float dx = ax - bx;
    float dy = ay - by;
    return sqrtf(dx * dx + dy * dy);
}

static bool isNearColEdge(const NPC &npc, uint32_t n, float tx, float ty, float buffer = 0.0f)
{
    SDL_FRect col = entityColAABB(npc, n);
    SDL_FPoint colCenter = entityColCenter(col);
    float nearReach = SDL_min(col.w, col.h) * 0.5f + buffer;
    return dist(colCenter.x, colCenter.y, tx, ty) < nearReach;
}

static void moveToward(float &x, float &y, float tx, float ty, float speed, float dt)
{
    float dx = tx - x;
    float dy = ty - y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;
    x += dx / d * speed * dt;
    y += dy / d * speed * dt;
}

static void moveColCenterToward(float &x, float &y, SDL_FRect col, float tx, float ty, float speed, float dt)
{
    SDL_FPoint colCenter = entityColCenter(col);
    float dx = tx - colCenter.x;
    float dy = ty - colCenter.y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;
    x += dx / d * speed * dt;
    y += dy / d * speed * dt;
}

static void updateMonster(uint32_t n, Context &ctx, float dt)
{
    auto &npc = ctx.data.npc;
    auto &ai = npc.ai;
    auto &player = ctx.data.player;

    SDL_FPoint npcColCenter    = entityColCenter(entityColAABB(npc, n));
    SDL_FPoint playerColCenter = entityColCenter(entityColAABB(player));

    float distToPlayer = dist(npcColCenter.x, npcColCenter.y, playerColCenter.x, playerColCenter.y);
    float distToSpawn  = dist(npcColCenter.x, npcColCenter.y, ai.spawn.x[n], ai.spawn.y[n]);

    switch (ai.state[n])
    {
    case NPCAiState::Idle:
        ai.idleTimer[n] -= dt;
        if (distToPlayer < DETECT_RADIUS)
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
        if (distToPlayer < DETECT_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToPlayer;
            break;
        }
        if (ai.patrolCount[n] == 0)
            break;
        uint32_t p = ai.patrolIndex[n];
        float tx = ai.spawn.x[n] + ai.patrol.x[n][p];
        float ty = ai.spawn.y[n] + ai.patrol.y[n][p];
        moveColCenterToward(npc.position.x[n], npc.position.y[n], entityColAABB(npc, n), tx, ty, MONSTER_SPEED, dt);
        if (isNearColEdge(npc, n, tx, ty, NEAR_POINT_BUFFER))
            ai.patrolIndex[n] = (p + 1) % ai.patrolCount[n];
        break;
    }

    case NPCAiState::GoToPlayer:
        if (distToSpawn > LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        moveColCenterToward(npc.position.x[n], npc.position.y[n], entityColAABB(npc, n), playerColCenter.x, playerColCenter.y, MONSTER_SPEED, dt);
        if (distToPlayer < ATTACK_REACH)
            ai.state[n] = NPCAiState::Attack;
        break;

    case NPCAiState::Attack:
        if (distToSpawn > LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        if (distToPlayer > ATTACK_REACH + 20.0f)
            ai.state[n] = NPCAiState::GoToPlayer;
        break;

    case NPCAiState::GoToSpawn:
        moveColCenterToward(npc.position.x[n], npc.position.y[n], entityColAABB(npc, n), ai.spawn.x[n], ai.spawn.y[n], MONSTER_SPEED, dt);
        if (isNearColEdge(npc, n, ai.spawn.x[n], ai.spawn.y[n], NEAR_POINT_BUFFER))
        {
            ai.idleTimer[n] = RandomIdleTimer();
            ai.state[n] = NPCAiState::Idle;
        }
        break;
    }
}

void NPCAiSystem(Context &ctx)
{
    float dt = ctx.frame.dt;
    auto &npc = ctx.data.npc;

    for (uint32_t n = 0; n < npc.npcCount; n++)
    {
        if (strcmp(npc.ai.type[n], "monster") == 0)
            updateMonster(n, ctx, dt);
    }
}
