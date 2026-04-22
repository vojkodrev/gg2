#include "DistToSpawn.h"
#include "Dist.h"
#include "EntityAABB.h"

float DistToSpawn(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter = EntityColCenter(EntityColAABB(ctx.data.npc, n));
    return Dist(npcColCenter.x, npcColCenter.y, ctx.data.npc.ai.spawn.x[n], ctx.data.npc.ai.spawn.y[n]);
}
