#include "NpcAutoAttackSystem.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../utils/collision/GetEntityColAABB.h"
#include "../rotation/HasMeleeWeaponRotationAnimation.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../statistics/SetHpDamage.h"
#include <SDL3/SDL.h>

void npcAutoAttackSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    const auto &target = npc.ai.target;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
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

        switch (target.type[i])
        {
        case EntityType::Player:
            setHpDamage(ctx.data.player.statistics, static_cast<uint32_t>(target.id[i]), NPC_MELEE_AUTO_ATTACK_DAMAGE);
            break;
        case EntityType::NPC:
            setHpDamage(ctx.data.npc.statistics, static_cast<uint32_t>(target.id[i]), NPC_MELEE_AUTO_ATTACK_DAMAGE);
            break;
        default:
            continue;
        }

        npc.autoAttack.hitTimer[i] = NPC_MELEE_AUTO_ATTACK_DELAY;
    }
}
