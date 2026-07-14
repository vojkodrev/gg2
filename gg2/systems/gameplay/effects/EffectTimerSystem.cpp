#include "EffectTimerSystem.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include <algorithm>

void effectTimerSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &effect = ctx.data.effect;

    for (uint32_t i = 0; i < effect.pool.count[0]; i++)
    {
        if (!effect.pool.active[0][i])
            continue;
        if (effect.destroyType[i] != DestroyEffectType::Timer)
            continue;

        effect.destroyTimer[i] = std::max(0.0f, effect.destroyTimer[i] - dt);
    }
}
