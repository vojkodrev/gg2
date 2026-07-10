#include "SpawnPlayerTargetedProjectileEffect.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/MathConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/DestroyEffectType.h"
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

int spawnPlayerTargetedProjectileEffect(
    Context &ctx,
    const EntityBase<1> &projectileBase,
    ProjectileType projectileType,
    int npcIndex,
    SDL_FColor tint)
{
    const int effectIndex =
        effectAlloc(ctx.data.effect, ctx.data.groups, ctx.data.player.group.id[0]);
    if (effectIndex == INVALID_ID)
        return INVALID_ID;

    ctx.data.effect.type[effectIndex] = EffectType::Projectile;
    ctx.data.effect.projectileType[effectIndex] = projectileType;
    ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::None;
    ctx.data.effect.parent.type[effectIndex] = EntityType::Player;
    ctx.data.effect.parent.id[effectIndex] = 0;
    ctx.data.effect.target.type[effectIndex] = EntityType::NPC;
    ctx.data.effect.target.id[effectIndex] = npcIndex;
    copyEntityBaseSlot(projectileBase, 0, ctx.data.effect.base, effectIndex);

    auto &effectBase = ctx.data.effect.base;
    effectBase.tint.r[effectIndex] = tint.r;
    effectBase.tint.g[effectIndex] = tint.g;
    effectBase.tint.b[effectIndex] = tint.b;
    effectBase.tint.a[effectIndex] = tint.a;
    const int frameIndex = effectBase.animation.frameIndex[effectIndex];
    const SDL_FRect originalAnchor = anchorOrCollision(effectBase.animation, effectIndex, frameIndex);
    const SDL_FPoint originalAnchorCenterWorld =
        entityColCenterWorld(originalAnchor, effectBase.position, effectIndex);

    const SDL_FPoint targetColCenter =
        entityColCenter(entityColAABB(ctx.data.npc.base, npcIndex));

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

    return effectIndex;
}
