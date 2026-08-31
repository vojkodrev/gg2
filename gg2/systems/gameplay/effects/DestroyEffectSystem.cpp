#include "DestroyEffectSystem.h"
#include "../../../structs/animation/AnimationState.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "EffectFree.h"
#include <cstdint>

void destroyEffectSystem(Context &ctx)
{
    auto &effect = ctx.data.effect;
    auto &castingEffectId =
        ctx.data.player.equipment.weapon.magic.castingEffectId[0];
    for (uint32_t i = 0; i < effect.pool.count[0]; i++)
    {
        if (!effect.pool.active[0][i])
            continue;

        bool shouldDestroy = false;
        if (effect.destroyType[i] == DestroyEffectType::None)
        {
            continue;
        }
        else if (effect.destroyType[i] == DestroyEffectType::AnimationEnd)
        {
            shouldDestroy =
                effect.base.animation.animationState[i] ==
                AnimationState::Finished;
        }
        else if (effect.destroyType[i] == DestroyEffectType::Timer)
        {
            shouldDestroy = effect.destroyTimer[i] <= 0.0f;
        }

        if (!shouldDestroy)
            continue;

        if (effect.type[i] == EffectType::FrostCast &&
            castingEffectId == static_cast<int>(i))
            castingEffectId = INVALID_ID;
        effectFree(effect, ctx.data.groups, i);
    }
}
