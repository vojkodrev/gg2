#include "DistToEntity.h"
#include "GetEntityColAABB.h"
#include "EntityColCenter.h"
#include "../math/Dist.h"

float distToEntity(Context &ctx, uint32_t n, EntityType targetType, int targetId)
{
    const SDL_FPoint npcColCenter =
        entityColCenter(mainEntityColAABB(ctx.data.npc.base, n));

    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
    if (targetType != EntityType::Player && targetType != EntityType::NPC)
        return 0.0f;

    const SDL_FPoint targetColCenter = entityColCenter(targetCol);
    return dist(npcColCenter.x, npcColCenter.y, targetColCenter.x, targetColCenter.y);
}
