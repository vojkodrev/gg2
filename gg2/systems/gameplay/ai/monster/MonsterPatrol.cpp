#include "MonsterPatrol.h"
#include "DetectTargetAndPursue.h"
#include "FollowNpcPatrolPath.h"

void monsterPatrol(uint32_t n, Context &ctx)
{
    if (detectTargetAndPursue(ctx, n))
        return;

    followNpcPatrolPath(ctx, n);
}
