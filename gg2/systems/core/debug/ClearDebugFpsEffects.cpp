#include "ClearDebugFpsEffects.h"
#include "../../../utils/queue/QueueDequeue.h"
#include "../../../utils/queue/QueueEmpty.h"
#include "../../gameplay/effects/EffectFree.h"

void clearDebugFpsEffects(Context &ctx)
{
    auto &queue = ctx.data.fps.characterEffectIds;
    while (!queueEmpty(queue, 0))
    {
        const int effectIndex = queueDequeue(queue, 0);
        effectFree(ctx.data.effect, ctx.data.groups, effectIndex);
    }
}
