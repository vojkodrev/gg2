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

inline void spawnNpcTextEffect(
    Context &ctx,
    uint32_t npcIndex,
    const std::string &text)
{
    const float totalW =
        text.size() * FONT_GLYPH_W +
        std::max<int>(0, static_cast<int>(text.size()) - 1) * DAMAGE_NUMBER_DIGIT_SEPARATOR;
    const SDL_FPoint npcColCenter = entityColCenter(entityColAABB(ctx.data.npc.base, npcIndex));
    const SDL_FPoint pos = {
        npcColCenter.x - totalW * 0.5f,
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

    spawnTextEffect(
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
