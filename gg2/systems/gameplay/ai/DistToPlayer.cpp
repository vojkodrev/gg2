#include "DistToPlayer.h"
#include "Dist.h"
#include "EntityBaseColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"

float distToPlayer(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter    = entityColCenter(entityBaseColAABB(ctx.data.npc.base, n));
    SDL_FPoint playerColCenter = entityColCenter(entityBaseColAABB(ctx.data.player.base, 0));
    return dist(npcColCenter.x, npcColCenter.y, playerColCenter.x, playerColCenter.y);
}
