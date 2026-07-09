#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/FontConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../ui/text/SpawnTextEffect.h"
#include <algorithm>
#include <string>

inline void createEntityTextEffect(
    Context &ctx,
    EntityType type,
    uint32_t entityIndex,
    const std::string &text)
{
    int groupId = -1;
    float entityY = 0.0f;
    SDL_FPoint entityCenter = {};

    switch (type)
    {
    case EntityType::Player:
        groupId = ctx.data.player.groupId;
        entityY = ctx.data.player.base.position.y[entityIndex];
        entityCenter = entityColCenter(entityColAABB(ctx.data.player.base, entityIndex));
        break;
    case EntityType::NPC:
        groupId = ctx.data.npc.groupId[entityIndex];
        entityY = ctx.data.npc.base.position.y[entityIndex];
        entityCenter = entityColCenter(entityColAABB(ctx.data.npc.base, entityIndex));
        break;
    default:
        return;
    }

    const float totalW =
        text.size() * FONT_GLYPH_W +
        std::max<int>(0, static_cast<int>(text.size()) - 1) * CHARACTER_SEPARATOR;
    const SDL_FPoint pos = {
        entityCenter.x - totalW * 0.5f,
        entityY - FONT_GLYPH_H - CHARACTER_DISTANCE_FROM_ENTITY
    };
    const SDL_FColor tint = {
        CHARACTER_TINT_R,
        CHARACTER_TINT_G,
        CHARACTER_TINT_B,
        CHARACTER_TINT_A
    };

    spawnTextEffect(
        ctx,
        groupId,
        type,
        static_cast<int>(entityIndex),
        DestroyEffectType::Timer,
        CHARACTER_DESTROY_TIME,
        text,
        pos,
        tint);
}
