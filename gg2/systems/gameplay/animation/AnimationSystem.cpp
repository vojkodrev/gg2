#include "AnimationSystem.h"
#include "Constants.h"

template<int N>
static void advanceAnimation(Animation<N> &anim, uint32_t count, uint64_t now)
{
    for (int i = 0; i < count; i++)
    {
        int fc = anim.frameCount[i];
        if (fc <= 1)
            continue;

        // Sum total cycle duration
        uint64_t cycleDuration = 0;
        for (int f = 0; f < fc; f++)
            cycleDuration += anim.frame.frameDuration[i][f];

        if (cycleDuration == 0)
            continue;

        if (anim.animationStartTime[i] == 0)
            anim.animationStartTime[i] = now;

        uint64_t elapsed = (now - anim.animationStartTime[i]) % cycleDuration;

        uint64_t accumulated = 0;
        for (int f = 0; f < fc; f++)
        {
            accumulated += anim.frame.frameDuration[i][f];
            if (elapsed < accumulated)
            {
                anim.frameIndex[i] = f;
                break;
            }
            if (f == fc - 1)
                anim.frameIndex[i] = f;
        }

    }
}

void animationSystem(Context &ctx)
{
    uint64_t now = ctx.frame.now;

    advanceAnimation(ctx.data.player.animation, 1u, now);
    advanceAnimation(ctx.data.npc.animation, ctx.data.npc.npcCount, now);
    advanceAnimation(ctx.data.object.animation, ctx.data.object.objectCount, now);
}
