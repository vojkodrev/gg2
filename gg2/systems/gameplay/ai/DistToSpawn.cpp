#include "DistToSpawn.h"
#include "Dist.h"
#include "EntityBaseColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"

float distToSpawn(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter = entityColCenter(entityBaseColAABB(ctx.data.npc.base, n));
    return dist(npcColCenter.x, npcColCenter.y, ctx.data.npc.ai.spawn.x[n], ctx.data.npc.ai.spawn.y[n]);
}
