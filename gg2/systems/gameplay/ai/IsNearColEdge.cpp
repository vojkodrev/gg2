#include "IsNearColEdge.h"
#include "Dist.h"
#include "EntityAABB.h"
#include <SDL3/SDL.h>

bool IsNearColEdge(Context &ctx, uint32_t n, float tx, float ty, float buffer)
{
    SDL_FRect col = EntityColAABB(ctx.data.npc, n);
    SDL_FPoint colCenter = EntityColCenter(col);
    float nearReach = SDL_min(col.w, col.h) * 0.5f + buffer;
    return Dist(colCenter.x, colCenter.y, tx, ty) < nearReach;
}
