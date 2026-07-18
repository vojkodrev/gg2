#include "MonsterPatrol.h"
#include "DetectTargetAndPursue.h"
#include "FollowNpcPatrolPath.h"

void monsterPatrol(uint32_t n, Context &ctx)
{
    if (detectTargetAndPursue(n, ctx))
        return;

    followNpcPatrolPath(n, ctx);
}
