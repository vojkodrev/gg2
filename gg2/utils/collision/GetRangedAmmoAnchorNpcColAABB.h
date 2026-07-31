#pragma once
#include "../../structs/core/Context.h"
#include "../../structs/equipment/WeaponType.h"
#include "EntityColAABB.h"
#include <SDL3/SDL.h>
#include <cstdint>

inline SDL_FRect getRangedAmmoAnchorNpcColAABB(
    const Context &ctx,
    uint32_t n)
{
    const auto &npc = ctx.data.npc;
    SDL_FRect moverBox = entityColAABB(npc.base, n);
    const auto &weapon = npc.equipment.weapon;
    if (weapon.type[n] != WeaponType::Ranged ||
        !weapon.ammoAnchor.hasAnchor[n][0])
        return moverBox;

    const SDL_FRect ammoAnchor = {
        weapon.base.position.x[n] + weapon.ammoAnchor.offX[n][0],
        weapon.base.position.y[n] + weapon.ammoAnchor.offY[n][0],
        weapon.ammoAnchor.w[n][0],
        weapon.ammoAnchor.h[n][0]
    };
    SDL_GetRectUnionFloat(&moverBox, &ammoAnchor, &moverBox);
    return moverBox;
}
