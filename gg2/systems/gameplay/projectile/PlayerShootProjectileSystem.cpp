#include "PlayerShootProjectileSystem.h"
#include "../../../structs/core/constants/MathConstants.h"
#include "../../../utils/pool/PoolAlloc.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../../utils/entity/ResetEntityBaseAnimationToInitial.h"
#include "../../../utils/animation/AnchorOrCollision.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/rect/AlignEntityToParentAnchor.h"
#include <cmath>

void playerShootProjectileSystem(Context &ctx)
{
    if (ctx.data.action.digit1Released)
    {
        const auto &playerAmmo = ctx.data.player.equipment.ammo.base;
        const auto &playerWeapon = ctx.data.player.equipment.weapon;
        if (!playerWeapon.hasAmmo[0])
            return;

        int effectIndex = poolAlloc(ctx.data.effect.pool);
        if (effectIndex == -1)
            return;

        ctx.data.effect.groupId[effectIndex] = ctx.data.player.groupId;
        ctx.data.effect.parent.type[effectIndex] = ParentType::Player;
        ctx.data.effect.parent.id[effectIndex] = 0;
        copyEntityBaseSlot(playerAmmo, 0, ctx.data.effect.base, effectIndex);

        auto &effectBase = ctx.data.effect.base;
        const int frameIndex = effectBase.animation.frameIndex[effectIndex];
        const SDL_FRect currentAnchor = anchorOrCollision(effectBase.animation, effectIndex, frameIndex);
        const SDL_FPoint currentAnchorCenterLocal = entityColCenter(currentAnchor);
        const SDL_FPoint anchorCenterWorld = {
            effectBase.position.x[effectIndex] + currentAnchorCenterLocal.x,
            effectBase.position.y[effectIndex] + currentAnchorCenterLocal.y
        };

        const SDL_FPoint cameraOff = ctx.data.camera.offset;
        const SDL_FPoint mouseWorld = {
            ctx.mouse.x - cameraOff.x,
            ctx.mouse.y - cameraOff.y
        };

        resetEntityBaseAnimationToInitial(effectBase, effectIndex);
        const SDL_FRect resetAnchor = anchorOrCollision(effectBase.animation, effectIndex, frameIndex);
        const SDL_FPoint anchorCenterLocal = entityColCenter(resetAnchor);
        alignEntityToAnchorCenter(effectBase, resetAnchor, anchorCenterWorld, effectIndex);
        effectBase.rotation.center.point.x[effectIndex] = anchorCenterLocal.x;
        effectBase.rotation.center.point.y[effectIndex] = anchorCenterLocal.y;
        effectBase.rotation.center.hasCenter[effectIndex] = true;
        effectBase.rotation.rotate[effectIndex] =
            std::atan2(mouseWorld.y - anchorCenterWorld.y, mouseWorld.x - anchorCenterWorld.x) * RAD_TO_DEG
            + effectBase.rotation.initialAngle[effectIndex];

        ctx.data.player.equipment.weapon.showAmmo[0] = false;
    }
}
