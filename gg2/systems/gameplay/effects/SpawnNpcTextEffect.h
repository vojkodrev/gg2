#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/FontConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../ui/text/SpawnDigitTextEffect.h"
#include <string>

inline void spawnNpcTextEffect(
    Context &ctx,
    uint32_t npcIndex,
    const std::string &text)
{
    const SDL_FPoint npcColCenter = entityColCenter(entityColAABB(ctx.data.npc.base, npcIndex));
    const SDL_FPoint pos = {
        npcColCenter.x,
        ctx.data.npc.base.position.y[npcIndex] -
        FONT_GLYPH_H -
        DAMAGE_NUMBER_DISTANCE_FROM_ENTITY
    };
    const SDL_FColor tint = {
        DAMAGE_NUMBER_TINT_R,
        DAMAGE_NUMBER_TINT_G,
        DAMAGE_NUMBER_TINT_B,
        DAMAGE_NUMBER_TINT_A
    };

    spawnDigitTextEffect(
        ctx,
        ctx.data.npc.groupId[npcIndex],
        EntityType::NPC,
        npcIndex,
        DestroyEffectType::Timer,
        DAMAGE_NUMBER_DESTROY_TIME,
        text,
        pos,
        tint);
}
