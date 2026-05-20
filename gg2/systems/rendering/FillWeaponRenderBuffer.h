#pragma once
#include "../../structs/equipment/Weapon.h"
#include "../../structs/core/Animation.h"
#include "../../structs/core/EntityPosition.h"
#include "../../structs/core/Facing.h"
#include "../../structs/render/RenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"
#include "../../utils/collision/EntityColCenter.h"
#include <cstdint>

template<int N>
inline void fillWeaponRenderBuffer(RenderBuffer &rb, const Weapon<N> &weaponData, const Animation<N> &parentAnimation, const EntityPosition<N> &parentPosition, const Facing<N> &parentFacing, uint32_t parentEntityIndex, uint32_t parentRenderIndex, uint32_t groupId)
{
    const auto &weapon = weaponData.animation;
    if (weapon.frameCount[parentEntityIndex] == 0)
        return;

    int wf = weapon.frameIndex[parentEntityIndex];
    uint32_t wn = rb.count++;

    rb.src.x[wn] = (float)weapon.frame.src.x[parentEntityIndex][wf];
    rb.src.y[wn] = (float)weapon.frame.src.y[parentEntityIndex][wf];
    rb.src.w[wn] = (float)weapon.frame.src.w[parentEntityIndex][wf];
    rb.src.h[wn] = (float)weapon.frame.src.h[parentEntityIndex][wf];

    rb.group.id[wn] = groupId;
    rb.group.zIndex[wn] = WEAPON_Z_INDEX;
    bool parentNeedsFlip = parentFacing.facing[parentEntityIndex] != weaponData.facing.initialFacing[parentEntityIndex];
    bool weaponFacingChanged = weaponData.facing.facing[parentEntityIndex] != weaponData.facing.initialFacing[parentEntityIndex];
    rb.flipX[wn] = parentNeedsFlip != weaponFacingChanged;

    rb.dst.w[wn] = parentPosition.w[parentEntityIndex] * weaponData.scale[parentEntityIndex];
    rb.dst.h[wn] = parentPosition.h[parentEntityIndex] * weaponData.scale[parentEntityIndex];

    auto anchorOrCollision = [](const Animation<N> &anim, uint32_t i, int f) -> SDL_FRect
    {
        SDL_FRect anchor = {
            anim.frame.anchor.offX[i][f],
            anim.frame.anchor.offY[i][f],
            anim.frame.anchor.w[i][f],
            anim.frame.anchor.h[i][f]};
        if (anchor.w > 0.0f && anchor.h > 0.0f)
            return anchor;
        return {
            anim.frame.collision.offX[i][f],
            anim.frame.collision.offY[i][f],
            anim.frame.collision.w[i][f],
            anim.frame.collision.h[i][f]};
    };
    auto worldAnchorRect = [](float dstX, float dstY, float dstW, const SDL_FRect &localAnchor, bool flipX) -> SDL_FRect
    {
        const float anchorX = flipX ? dstW - localAnchor.x - localAnchor.w : localAnchor.x;
        return {dstX + anchorX, dstY + localAnchor.y, localAnchor.w, localAnchor.h};
    };

    int pf = parentAnimation.frameIndex[parentEntityIndex];
    SDL_FRect parentAnchor = anchorOrCollision(parentAnimation, parentEntityIndex, pf);
    bool parentFlipX = parentFacing.facing[parentEntityIndex] != parentFacing.initialFacing[parentEntityIndex];
    SDL_FRect parentAnchorWorld = worldAnchorRect(
        parentPosition.x[parentEntityIndex],
        parentPosition.y[parentEntityIndex],
        parentPosition.w[parentEntityIndex],
        parentAnchor,
        parentFlipX);

    SDL_FRect weaponAnchor = anchorOrCollision(weapon, parentEntityIndex, wf);
    SDL_FRect weaponAnchorWorld = worldAnchorRect(
        0.0f,
        0.0f,
        rb.dst.w[wn],
        weaponAnchor,
        rb.flipX[wn]);

    SDL_FPoint parentCenter = entityColCenter(parentAnchorWorld);
    SDL_FPoint weaponCenter = entityColCenter(weaponAnchorWorld);
    rb.dst.x[wn] = parentCenter.x - weaponCenter.x;
    rb.dst.y[wn] = parentCenter.y - weaponCenter.y;
    rb.dst.sortY[wn] = rb.dst.sortY[parentRenderIndex];

    float weaponRotate = (float)weapon.frame.src.rotate[parentEntityIndex][wf];
    rb.src.rotate[wn] = rb.flipX[wn] ? -weaponRotate : weaponRotate;
}
