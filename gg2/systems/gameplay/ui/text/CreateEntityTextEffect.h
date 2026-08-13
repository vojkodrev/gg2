#pragma once
#include "../../../../structs/core/Context.h"
#include "../../../../structs/core/constants/FontConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"
#include "../../../../structs/entity/EntityType.h"
#include "../../../../utils/collision/EntityColAABB.h"
#include "../../../../utils/collision/EntityColCenter.h"
#include "CreateTextEffect.h"
#include <algorithm>
#include <string>

template<int N>
inline void createEntityTextEffect(
    Context &ctx,
    int groupId,
    EntityType type,
    uint32_t entityIndex,
    const EntityBase<N> &entityBase,
    const std::string &text)
{
    const float entityY = entityBase.position.y[entityIndex];
    const SDL_FPoint entityCenter =
        entityColCenter(entityColAABB(entityBase, entityIndex));

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

    createTextEffect(
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
