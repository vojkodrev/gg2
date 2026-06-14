#include "DistToNpcSpawn.h"
#include "EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/math/Dist.h"

float distToNpcSpawn(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter = entityColCenter(entityColAABB(ctx.data.npc.base, n));
    return dist(npcColCenter.x, npcColCenter.y, ctx.data.npc.ai.spawn.x[n], ctx.data.npc.ai.spawn.y[n]);
}
