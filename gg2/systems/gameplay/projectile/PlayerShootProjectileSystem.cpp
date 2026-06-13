#include "PlayerShootProjectileSystem.h"
#include "../../../structs/core/constants/MathConstants.h"
#include "../../../utils/effects/AllocEffect.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../../utils/entity/ResetEntityBaseAnimationToInitial.h"
#include "../../../utils/animation/AnchorOrCollision.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/collision/EntityColCenterWorld.h"
#include "../../../utils/rect/AlignEntityToAnchorCenter.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include "../flipx/MirrorEntityAnchorsAndCollisionOffsets.h"
#include <cmath>

void playerShootProjectileSystem(Context &ctx)
{
    if (ctx.data.action.digit1Released)
    {
        const auto &playerAmmo = ctx.data.player.equipment.ammo.base;
        const auto &playerWeapon = ctx.data.player.equipment.weapon;
        if (!playerWeapon.hasAmmo[0])
            return;

        int effectIndex = allocEffect(ctx.data.effect, ctx.data.groups, ctx.data.player.groupId);
        if (effectIndex == -1)
            return;

        ctx.data.effect.parent.type[effectIndex] = ParentType::Player;
        ctx.data.effect.parent.id[effectIndex] = 0;
        copyEntityBaseSlot(playerAmmo, 0, ctx.data.effect.base, effectIndex);

        auto &effectBase = ctx.data.effect.base;
        const int frameIndex = effectBase.animation.frameIndex[effectIndex];
        const SDL_FRect originalAnchor = anchorOrCollision(effectBase.animation, effectIndex, frameIndex);
        const SDL_FPoint originalAnchorCenterWorld =
            entityColCenterWorld(originalAnchor, effectBase.position, effectIndex);
        ctx.data.effect.start.x[effectIndex] = originalAnchorCenterWorld.x;
        ctx.data.effect.start.y[effectIndex] = originalAnchorCenterWorld.y;

        const SDL_FPoint cameraOff = ctx.data.camera.offset;
        const SDL_FPoint mouseWorld = {
            ctx.mouse.x - cameraOff.x,
            ctx.mouse.y - cameraOff.y
        };
        ctx.data.effect.target.x[effectIndex] = mouseWorld.x;
        ctx.data.effect.target.y[effectIndex] = mouseWorld.y;

        resetEntityBaseAnimationToInitial(effectBase, effectIndex);
        mirrorEntityAnchorsAndCollisionOffsets(effectBase, effectIndex);

        const SDL_FRect resetAnchor = anchorOrCollision(effectBase.animation, effectIndex, frameIndex);
        const SDL_FPoint resetAnchorCenterLocal =
            entityColCenter(resetAnchor);
        const SDL_FPoint collisionCenterLocal =
            entityColCenter(effectBase.animation.frame.collision, effectIndex, frameIndex);

        const float initialAngle =
            std::atan2(
                collisionCenterLocal.y - resetAnchorCenterLocal.y,
                collisionCenterLocal.x - resetAnchorCenterLocal.x) * RAD_TO_DEG;
        const float aimAngle =
            std::atan2(
                mouseWorld.y - originalAnchorCenterWorld.y,
                mouseWorld.x - originalAnchorCenterWorld.x) * RAD_TO_DEG;

        alignEntityToAnchorCenter(effectBase, resetAnchor, originalAnchorCenterWorld, effectIndex);

        effectBase.rotation.center.point.x[effectIndex] = resetAnchorCenterLocal.x;
        effectBase.rotation.center.point.y[effectIndex] = resetAnchorCenterLocal.y;
        effectBase.rotation.center.hasCenter[effectIndex] = true;
        effectBase.rotation.rotate[effectIndex] = aimAngle - initialAngle;

        rotateRectCenter(
            effectBase.animation.frame.collision.offX[effectIndex][frameIndex],
            effectBase.animation.frame.collision.offY[effectIndex][frameIndex],
            effectBase.animation.frame.collision.w[effectIndex][frameIndex],
            effectBase.animation.frame.collision.h[effectIndex][frameIndex],
            resetAnchorCenterLocal.x,
            resetAnchorCenterLocal.y,
            effectBase.rotation.rotate[effectIndex]);

        ctx.data.player.equipment.weapon.showAmmo[0] = false;
    }
}
