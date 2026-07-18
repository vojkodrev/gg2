#include "FriendlyPatrol.h"
#include "FollowNpcPatrolPath.h"

void friendlyPatrol(uint32_t n, Context &ctx)
{
    followNpcPatrolPath(ctx, n);
}
