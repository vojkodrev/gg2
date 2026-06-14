#include "DistToPlayer.h"
#include "EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/math/Dist.h"

float distToPlayer(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter    = entityColCenter(entityColAABB(ctx.data.npc.base, n));
    SDL_FPoint playerColCenter = entityColCenter(entityColAABB(ctx.data.player.base, 0));
    return dist(npcColCenter.x, npcColCenter.y, playerColCenter.x, playerColCenter.y);
}
