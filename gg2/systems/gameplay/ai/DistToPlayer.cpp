#include "DistToPlayer.h"
#include "Dist.h"
#include "EntityColAABBPlayer.h"
#include "EntityColAABBNPC.h"
#include "../../../utils/collision/EntityColCenter.h"

float distToPlayer(Context &ctx, uint32_t n)
{
    SDL_FPoint npcColCenter    = entityColCenter(entityColAABB(ctx.data.npc, n));
    SDL_FPoint playerColCenter = entityColCenter(entityColAABB(ctx.data.player));
    return dist(npcColCenter.x, npcColCenter.y, playerColCenter.x, playerColCenter.y);
}
