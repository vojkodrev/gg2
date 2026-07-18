#include "FriendlyPatrol.h"
#include "FollowNpcPatrolPath.h"

void friendlyPatrol(Context &ctx, uint32_t n)
{
    followNpcPatrolPath(ctx, n);
}
