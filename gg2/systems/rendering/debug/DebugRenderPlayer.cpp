#include "DebugRenderPlayer.h"
#include "DebugRenderEntityBase.h"
#include "DebugRenderEquipment.h"

void debugRenderPlayer(const Context &ctx)
{
    const auto &debug = ctx.data.debug;
    const auto &player = ctx.data.player;

    if (debug.showCollision)
        debugRenderEntityBase(ctx, player.base, 0, SDL_Color{255, 0, 0, 255});

    if (debug.showWeaponCollision || debug.showAmmoCollision)
        debugRenderEquipment(ctx, player.equipment, 0);
}
