#include "NPCAiSystem.h"
#include "EntityAABB.h"
#include <cmath>
#include <cstdlib>

static constexpr float MONSTER_SPEED    = 60.0f;
static constexpr float DETECT_RADIUS    = 200.0f;
static constexpr float ATTACK_REACH     = 20.0f;
static constexpr float LEASH_RADIUS     = 400.0f;
static constexpr float NEAR_POINT_REACH = 8.0f;
static constexpr float IDLE_TIME_MIN    = 1.0f;
static constexpr float IDLE_TIME_MAX    = 3.0f;

static float dist(float ax, float ay, float bx, float by)
{
    float dx = ax - bx;
    float dy = ay - by;
    return sqrtf(dx * dx + dy * dy);
}

static void moveToward(float &x, float &y, float tx, float ty, float speed, float dt)
{
    float dx = tx - x;
    float dy = ty - y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d < 0.5f)
        return;
    x += dx / d * speed * dt;
    y += dy / d * speed * dt;
}

static void updateMonster(uint32_t n, Context &ctx, float dt)
{
    auto &npc = ctx.data.npc;
    auto &ai = npc.ai;
    auto &player = ctx.data.player;

    SDL_FRect npcBox = entityAABB(npc, n);
    float npcCx = npcBox.x + npcBox.w * 0.5f;
    float npcCy = npcBox.y + npcBox.h * 0.5f;

    SDL_FRect playerBox = entityAABB(player);
    float playerCx = playerBox.x + playerBox.w * 0.5f;
    float playerCy = playerBox.y + playerBox.h * 0.5f;

    float distToPlayer = dist(npcCx, npcCy, playerCx, playerCy);
    float distToSpawn  = dist(npcCx, npcCy, ai.spawn.x[n], ai.spawn.y[n]);

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
        moveToward(npc.position.x[n], npc.position.y[n], tx, ty, MONSTER_SPEED, dt);
        if (dist(npcCx, npcCy, tx, ty) < NEAR_POINT_REACH)
            ai.patrolIndex[n] = (p + 1) % ai.patrolCount[n];
        break;
    }

    case NPCAiState::GoToPlayer:
        if (distToSpawn > LEASH_RADIUS)
        {
            ai.state[n] = NPCAiState::GoToSpawn;
            break;
        }
        moveToward(npc.position.x[n], npc.position.y[n], playerCx, playerCy, MONSTER_SPEED, dt);
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
        moveToward(npc.position.x[n], npc.position.y[n], ai.spawn.x[n], ai.spawn.y[n], MONSTER_SPEED, dt);
        if (dist(npcCx, npcCy, ai.spawn.x[n], ai.spawn.y[n]) < NEAR_POINT_REACH)
        {
            ai.idleTimer[n] = IDLE_TIME_MIN + (float)rand() / RAND_MAX * (IDLE_TIME_MAX - IDLE_TIME_MIN);
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
