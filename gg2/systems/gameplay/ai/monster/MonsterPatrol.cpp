#include "MonsterPatrol.h"
#include "DetectTargetAndPursue.h"
#include "FollowNpcPatrolPath.h"

void monsterPatrol(Context &ctx, uint32_t n)
{
    if (detectTargetAndPursue(ctx, n))
        return;

    followNpcPatrolPath(ctx, n);
}
