#pragma once
#include "../../../../structs/core/Context.h"
#include "../../../../structs/core/EntityType.h"
#include "../../../../structs/core/constants/FontConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"
#include "../../../../structs/effect/DestroyEffectType.h"
#include "../../../../structs/effect/EffectType.h"
#include "../../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../../../utils/queue/Queue.h"
#include "../../../../utils/queue/QueueEnqueue.h"
#include "../../effects/EffectAlloc.h"
#include <SDL3/SDL.h>
#include <string>

template<uint32_t TQueueSize>
inline void createTextEffect(
    Context &ctx,
    int groupId,
    EntityType parentType,
    int parentId,
    DestroyEffectType destroyType,
    float destroyTimer,
    const std::string &text,
    SDL_FPoint pos,
    SDL_FColor tint,
    Queue<int, 1, TQueueSize> *effectIdsQueue)
{
    const auto &templateBase = ctx.data.effectTemplate.base;
    float x = pos.x;

    for (uint32_t i = 0; i < text.size(); i++)
    {
        const unsigned char glyph = static_cast<unsigned char>(text[i]);
        const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, groupId);
        if (effectIndex == INVALID_ID)
            return;

        if (effectIdsQueue != nullptr)
            queueEnqueue(*effectIdsQueue, 0, effectIndex);

        copyEntityBaseSlot(
            templateBase,
            ctx.data.effectTemplate.fontIndex + glyph,
            ctx.data.effect.base,
            effectIndex);

        ctx.data.effect.type[effectIndex] = EffectType::Character;
        ctx.data.effect.destroyType[effectIndex] = destroyType;
        ctx.data.effect.destroyTimer[effectIndex] = destroyTimer;
        ctx.data.effect.parent.type[effectIndex] = parentType;
        ctx.data.effect.parent.id[effectIndex] = parentId;
        ctx.data.effect.base.position.x[effectIndex] = x;
        ctx.data.effect.base.position.y[effectIndex] = pos.y;
        ctx.data.effect.base.position.absolute[effectIndex] =
            parentType == EntityType::ActionBarIcon || parentType == EntityType::Window;
        ctx.data.effect.base.tint.r[effectIndex] = tint.r;
        ctx.data.effect.base.tint.g[effectIndex] = tint.g;
        ctx.data.effect.base.tint.b[effectIndex] = tint.b;
        ctx.data.effect.base.tint.a[effectIndex] = tint.a;

        const float separator =
            text[i] == '.'
            ? CHARACTER_ADVANCE_AFTER_PERIOD
            : text[i] == '(' || text[i] == ')'
            ? CHARACTER_ADVANCE_AFTER_PARENTHESIS
            : CHARACTER_SEPARATOR;
        x += FONT_GLYPH_W + separator;
    }
}

inline void createTextEffect(
    Context &ctx,
    int groupId,
    EntityType parentType,
    int parentId,
    DestroyEffectType destroyType,
    float destroyTimer,
    const std::string &text,
    SDL_FPoint pos,
    SDL_FColor tint)
{
    createTextEffect(
        ctx,
        groupId,
        parentType,
        parentId,
        destroyType,
        destroyTimer,
        text,
        pos,
        tint,
        static_cast<Queue<int, 1, 1> *>(nullptr));
}
