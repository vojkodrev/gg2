#pragma once
#include "Context.h"
#include "EntityColCenter.h"
#include "EntityColCenterWorld.h"
#include "RenderDebugLine.h"
#include "../../../structs/equipment/Equipment.h"
#include <cstdint>

template<int N>
inline void renderTargetVisibleLine(
    const Context &ctx,
    const Equipment<N> &equipment,
    uint32_t entityIndex,
    const SDL_FRect &targetCol)
{
    const SDL_FRect ammoAnchor = {
        equipment.weapon.ammoAnchor.offX[entityIndex][0],
        equipment.weapon.ammoAnchor.offY[entityIndex][0],
        equipment.weapon.ammoAnchor.w[entityIndex][0],
        equipment.weapon.ammoAnchor.h[entityIndex][0]
    };
    const SDL_FPoint ammoAnchorCenter = entityColCenterWorld(
        ammoAnchor,
        equipment.weapon.base.position,
        entityIndex);
    const SDL_FPoint targetCenter = entityColCenter(targetCol);
    const SDL_FPoint offset = ctx.data.camera.offset;

    renderDebugLine(
        ctx,
        ammoAnchorCenter.x + offset.x,
        ammoAnchorCenter.y + offset.y,
        targetCenter.x + offset.x,
        targetCenter.y + offset.y);
}
