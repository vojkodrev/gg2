#include "DistToSpawn.h"
#include "Dist.h"
#include "EntityColAABBNPC.h"
#include "../../../utils/collision/EntityColCenter.h"

float distToSpawn(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter = entityColCenter(entityColAABB(ctx.data.npc, n));
    return dist(npcColCenter.x, npcColCenter.y, ctx.data.npc.ai.spawn.x[n], ctx.data.npc.ai.spawn.y[n]);
}
