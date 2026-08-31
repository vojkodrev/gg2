#include "PlayerFrostBoltAttackSystem.h"
#include "../../../structs/core/constants/FrostBoltConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/ZIndexConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../structs/ui/CastType.h"
#include "../../effects/CopyEffect.h"
#include "../../effects/EffectAlloc.h"
#include "../../scale/ScaleEntityBaseLocations.h"
#include "../../../utils/collision/EntityColCenterWorld.h"
#include "../../../utils/rect/CenteredRect.h"

void playerFrostBoltAttackSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    auto &weapon = player.equipment.weapon;
    if (!ctx.data.action.digit3Released ||
        player.globalCooldownTimer > 0.0f ||
        player.castbar.timer[0] > 0.0f ||
        player.selectedNpc == INVALID_ID ||
        !weapon.exists[0] ||
        weapon.type[0] != WeaponType::Magic)
        return;

    const int weaponFrameIndex = weapon.base.animation.frameIndex[0];
    const auto &spellAnchor = weapon.magic.spellAnchor;
    if (!spellAnchor.exists[0][weaponFrameIndex][0])
        return;

    const int effectIndex = effectAlloc(
        ctx.data.effect,
        ctx.data.groups,
        player.group.id[0]);
    if (effectIndex == INVALID_ID)
        return;

    auto &effect = ctx.data.effect;
    copyEffect(
        ctx,
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.frostCastIndex,
        effectIndex);
    scaleEntityBaseLocations(effect.base, effectIndex);

    const SDL_FRect spellAnchorRect = {
        spellAnchor.offX[0][weaponFrameIndex][0],
        spellAnchor.offY[0][weaponFrameIndex][0],
        spellAnchor.w[0][weaponFrameIndex][0],
        spellAnchor.h[0][weaponFrameIndex][0]
    };
    const SDL_FPoint spellAnchorCenter = entityColCenterWorld(
        spellAnchorRect,
        weapon.base.position,
        0);
    const SDL_FRect effectRect = centeredRect(
        spellAnchorCenter,
        effect.base.position.w[effectIndex],
        effect.base.position.h[effectIndex]);
    effect.base.position.x[effectIndex] = effectRect.x;
    effect.base.position.y[effectIndex] = effectRect.y;
    effect.base.position.dirty[effectIndex] = true;
    effect.type[effectIndex] = EffectType::FrostCast;
    effect.zIndex[effectIndex] = EFFECT_FROST_CAST_Z_INDEX;
    effect.destroyType[effectIndex] = DestroyEffectType::Timer;
    effect.destroyTimer[effectIndex] = FROST_BOLT_CAST_TIME;
    effect.parent.type[effectIndex] = EntityType::Player;
    effect.parent.id[effectIndex] = 0;
    weapon.magic.castingEffectId[0] = effectIndex;

    player.castbar.type[0] = CastType::FrostBolt;
    player.castbar.timer[0] = FROST_BOLT_CAST_TIME;
    player.castbar.duration[0] = FROST_BOLT_CAST_TIME;
    player.castbar.hideTimer[0] = 0.0f;
    player.castbar.progressBar.dirty[0] = true;
}
