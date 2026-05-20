#include "EquipmentSystem.h"
#include "../../utils/collision/EntityColCenter.h"

template<int N>
static void updateWeaponAttachment(
    Weapon<N> &weaponData,
    const Animation<N> &parentAnimation,
    const EntityPosition<N> &parentPosition,
    const Facing<N> &parentFacing,
    uint32_t i)
{
    auto &weapon = weaponData.animation;
    if (weapon.frameCount[i] == 0)
        return;

    int wf = weapon.frameIndex[i];
    int pf = parentAnimation.frameIndex[i];

    auto anchorOrCollision = [](const Animation<N> &anim, uint32_t index, int frame) -> SDL_FRect
    {
        SDL_FRect anchor = {
            anim.frame.anchor.offX[index][frame],
            anim.frame.anchor.offY[index][frame],
            anim.frame.anchor.w[index][frame],
            anim.frame.anchor.h[index][frame]};
        if (anchor.w > 0.0f && anchor.h > 0.0f)
            return anchor;
        return {
            anim.frame.collision.offX[index][frame],
            anim.frame.collision.offY[index][frame],
            anim.frame.collision.w[index][frame],
            anim.frame.collision.h[index][frame]};
    };
    auto worldAnchorRect = [](float dstX, float dstY, float dstW, const SDL_FRect &localAnchor, bool flipX) -> SDL_FRect
    {
        const float anchorX = flipX ? dstW - localAnchor.x - localAnchor.w : localAnchor.x;
        return {dstX + anchorX, dstY + localAnchor.y, localAnchor.w, localAnchor.h};
    };

    bool parentFlipX = parentFacing.flipX[i];
    bool weaponFlipX = weaponData.facing.flipX[i];

    weaponData.position.w[i] = parentPosition.w[i] * weaponData.scale[i];
    weaponData.position.h[i] = parentPosition.h[i] * weaponData.scale[i];

    SDL_FRect parentAnchor = anchorOrCollision(parentAnimation, i, pf);
    SDL_FRect parentAnchorWorld = worldAnchorRect(
        parentPosition.x[i],
        parentPosition.y[i],
        parentPosition.w[i],
        parentAnchor,
        parentFlipX);

    SDL_FRect weaponAnchor = anchorOrCollision(weapon, i, wf);
    SDL_FRect weaponAnchorWorld = worldAnchorRect(
        0.0f,
        0.0f,
        weaponData.position.w[i],
        weaponAnchor,
        weaponFlipX);

    SDL_FPoint parentCenter = entityColCenter(parentAnchorWorld);
    SDL_FPoint weaponCenter = entityColCenter(weaponAnchorWorld);
    weaponData.position.x[i] = parentCenter.x - weaponCenter.x;
    weaponData.position.y[i] = parentCenter.y - weaponCenter.y;
}

void equipmentSystem(Context &ctx)
{
    updateWeaponAttachment(ctx.data.player.equipment.weapon, ctx.data.player.animation, ctx.data.player.position, ctx.data.player.facing, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        updateWeaponAttachment(ctx.data.npc.equipment.weapon, ctx.data.npc.animation, ctx.data.npc.position, ctx.data.npc.facing, i);
}
