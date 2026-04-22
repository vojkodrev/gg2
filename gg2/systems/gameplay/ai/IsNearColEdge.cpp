#include "IsNearColEdge.h"
#include "Dist.h"
#include "EntityAABB.h"
#include <SDL3/SDL.h>

bool isNearColEdge(Context &ctx, uint32_t n, float tx, float ty, float buffer)
{
    SDL_FRect col = entityColAABB(ctx.data.npc, n);
    SDL_FPoint colCenter = entityColCenter(col);
    float nearReach = SDL_min(col.w, col.h) * 0.5f + buffer;
    return dist(colCenter.x, colCenter.y, tx, ty) < nearReach;
}
