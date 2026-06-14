#include "PlayerDepthSystem.h"
#include "SetEntityBaseDepthY.h"

void playerDepthSystem(Context &ctx)
{
    setEntityBaseDepthY(ctx.data.player.base, 0);
}
