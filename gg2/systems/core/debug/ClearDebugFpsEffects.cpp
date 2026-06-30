#include "ClearDebugFpsEffects.h"
#include "../../../utils/queue/QueueDequeue.h"
#include "../../../utils/queue/QueueEmpty.h"
#include "../../gameplay/effects/EffectFree.h"

void clearDebugFpsEffects(Context &ctx)
{
    auto &queue = ctx.data.fps.digitEffectIds;
    while (!queueEmpty(queue))
    {
        const int effectIndex = queueDequeue(queue);
        effectFree(ctx.data.effect, ctx.data.groups, effectIndex);
    }
}
