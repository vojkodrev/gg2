#include "PlayerShootProjectileSystem.h"
#include "../../../structs/core/constants/MathConstants.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../effects/EffectAlloc.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../../utils/entity/ResetEntityBaseAnimationToInitial.h"
#include "../../../utils/animation/AnchorOrCollision.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/collision/EntityColCenterWorld.h"
#include "../../../utils/rect/AlignEntityToAnchorCenter.h"
#include "../../../utils/rect/RotateRectCenter.h"
#include "../flipx/MirrorEntityAnchorsAndCollisionOffsets.h"
#include <cmath>

void playerShootProjectileSystem(Context &ctx)
{
    if (ctx.data.player.autoAttack.active && ctx.data.player.autoAttack.attackTimer == 0.0f)
    {
        const int npcIndex = ctx.data.player.selectedNpc;
        if (npcIndex == -1)
            return;
        if (!ctx.data.npc.active[npcIndex])
            return;
        if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
            return;

        const auto &playerAmmo = ctx.data.player.equipment.ammo.base;
        const auto &playerWeapon = ctx.data.player.equipment.weapon;
        if (playerWeapon.type[0] != WeaponType::Ranged)
            return;

        int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, ctx.data.player.groupId);
        if (effectIndex == -1)
            return;

        ctx.data.effect.type[effectIndex] = EffectType::Projectile;
        ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::None;
        ctx.data.effect.parent.type[effectIndex] = EntityType::Player;
        ctx.data.effect.parent.id[effectIndex] = 0;
        ctx.data.effect.target.type[effectIndex] = EntityType::NPC;
        ctx.data.effect.target.id[effectIndex] = npcIndex;
        ctx.data.player.autoAttack.attackTimer = PLAYER_AUTO_ATTACK_DELAY;
        copyEntityBaseSlot(playerAmmo, 0, ctx.data.effect.base, effectIndex);

        auto &effectBase = ctx.data.effect.base;
        effectBase.tint.r[effectIndex] = CLEAR_TINT_R;
        effectBase.tint.g[effectIndex] = CLEAR_TINT_G;
        effectBase.tint.b[effectIndex] = CLEAR_TINT_B;
        effectBase.tint.a[effectIndex] = CLEAR_TINT_A;
        const int frameIndex = effectBase.animation.frameIndex[effectIndex];
        const SDL_FRect originalAnchor = anchorOrCollision(effectBase.animation, effectIndex, frameIndex);
        const SDL_FPoint originalAnchorCenterWorld =
            entityColCenterWorld(originalAnchor, effectBase.position, effectIndex);

        const SDL_FPoint targetColCenter =
            entityColCenter(entityColAABB(ctx.data.npc.base, npcIndex));
        const float aimDx = targetColCenter.x - originalAnchorCenterWorld.x;
        const float aimDy = targetColCenter.y - originalAnchorCenterWorld.y;

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
                targetColCenter.y - originalAnchorCenterWorld.y,
                targetColCenter.x - originalAnchorCenterWorld.x) * RAD_TO_DEG;

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
