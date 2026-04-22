#include "DistToPlayer.h"
#include "Dist.h"
#include "EntityAABB.h"

float DistToPlayer(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter    = EntityColCenter(EntityColAABB(ctx.data.npc, n));
    SDL_FPoint playerColCenter = EntityColCenter(EntityColAABB(ctx.data.player));
    return Dist(npcColCenter.x, npcColCenter.y, playerColCenter.x, playerColCenter.y);
}
