#include "NpcAutoAttackSystem.h"
#include "ApplyAttackDamage.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../../utils/collision/GetEntityColAABB.h"
#include "../rotation/HasMeleeWeaponRotationAnimation.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include <SDL3/SDL.h>

void npcAutoAttackSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    const auto &target = npc.ai.target;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;
        if (npc.ai.type[i] != NPCAiType::MonsterMelee)
            continue;
        if (npc.autoAttack.hitTimer[i] > 0.0f)
            continue;

        auto &weapon = npc.equipment.weapon;
        if (!hasMeleeWeaponRotationAnimation(weapon, i))
            continue;
        if (!isRotationAnimationRunning(weapon.base, i))
            continue;

        const SDL_FRect targetCol = getEntityColAABB(ctx, target.type[i], target.id[i]);
        const SDL_FRect weaponCol = entityColAABB(weapon.base, i);
        if (!SDL_HasRectIntersectionFloat(&weaponCol, &targetCol))
            continue;

        if (target.type[i] != EntityType::Player &&
            target.type[i] != EntityType::NPC)
            continue;

        const uint32_t targetId = static_cast<uint32_t>(target.id[i]);
        if (target.type[i] == EntityType::Player)
        {
            applyAttackDamage(
                ctx,
                target.type[i],
                targetId,
                ctx.data.player.statistics,
                ctx.data.player.group,
                ctx.data.player.base,
                NPC_MELEE_AUTO_ATTACK_DAMAGE,
                NPC_MELEE_AUTO_ATTACK_DAMAGE_RANDOM_RANGE);
        }
        else if (target.type[i] == EntityType::NPC)
        {
            applyAttackDamage(
                ctx,
                target.type[i],
                targetId,
                ctx.data.npc.statistics,
                ctx.data.npc.group,
                ctx.data.npc.base,
                NPC_MELEE_AUTO_ATTACK_DAMAGE,
                NPC_MELEE_AUTO_ATTACK_DAMAGE_RANDOM_RANGE);
        }
        else
            continue;

        npc.autoAttack.hitTimer[i] = NPC_MELEE_AUTO_ATTACK_DELAY;
    }
}
