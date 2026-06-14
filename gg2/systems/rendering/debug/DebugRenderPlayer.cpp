#include "DebugRenderPlayer.h"
#include "DebugRenderEntityBase.h"
#include "DebugRenderEquipment.h"

void debugRenderPlayer(const Context &ctx)
{
    const auto &player = ctx.data.player;
    const bool showCollision = ctx.data.debug.showCollision;

    if (showCollision)
        debugRenderEntityBase(ctx, player.base, 0, SDL_Color{255, 0, 0, 255});

    debugRenderEquipment(ctx, player.equipment, 0);
}
