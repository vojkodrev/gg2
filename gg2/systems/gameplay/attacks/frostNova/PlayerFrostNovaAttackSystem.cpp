#include "PlayerFrostNovaAttackSystem.h"
#include "../../../structs/core/constants/FrostNovaConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../effects/CopyEffect.h"
#include "../../scale/ScaleEntityBaseLocations.h"
#include "../../../utils/rect/CenteredRect.h"
#include "../../../utils/rect/EntityPositionCenter.h"
#include "../../effects/EffectAlloc.h"

void playerFrostNovaAttackSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    const auto &weapon = player.equipment.weapon;
    if (!ctx.data.action.digit2Released ||
        player.frostNovaCooldownTimer > 0.0f ||
        !weapon.exists[0] ||
        weapon.type[0] != WeaponType::Magic)
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
        ctx.data.effectTemplate.frostNovaIndex,
        effectIndex);
    scaleEntityBaseLocations(effect.base, effectIndex);

    const SDL_FRect effectRect = centeredRect(
        entityPositionCenter(player.base.position, 0),
        effect.base.position.w[effectIndex],
        effect.base.position.h[effectIndex]);
    effect.base.position.x[effectIndex] = effectRect.x;
    effect.base.position.y[effectIndex] = effectRect.y;
    effect.base.position.dirty[effectIndex] = true;

    effect.type[effectIndex] = EffectType::FrostNova;
    effect.destroyType[effectIndex] = DestroyEffectType::AnimationEnd;
    effect.parent.type[effectIndex] = EntityType::Player;
    effect.parent.id[effectIndex] = 0;

    player.frostNovaCooldownTimer = FROST_NOVA_COOLDOWN_TIME;
}
