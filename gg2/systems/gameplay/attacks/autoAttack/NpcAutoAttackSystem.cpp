#include "NpcAutoAttackSystem.h"
#include "../damage/ApplyAttackDamage.h"
#include "../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/GetEntityColAABB.h"
#include "../rotation/HasMeleeWeaponRotationAnimation.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include <SDL3/SDL.h>

void npcAutoAttackSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    const auto &target = npc.ai.target;

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!npc.active[entityIndex])
            continue;
        if (npc.ai.type[entityIndex] != NPCAiType::MonsterMelee)
            continue;
        if (npc.autoAttack.hitTimer[entityIndex] > 0.0f)
            continue;

        auto &weapon = npc.equipment.weapon;
        if (!hasMeleeWeaponRotationAnimation(weapon, entityIndex))
            continue;
        if (!isRotationAnimationRunning(weapon.base, entityIndex))
            continue;

        const SDL_FRect targetCol = getEntityColAABB(
            ctx,
            target.type[entityIndex],
            target.id[entityIndex]);
        bool targetHit = false;
        for (int collisionIndex = 0;
            collisionIndex < MAX_FRAME_COLLISIONS;
            collisionIndex++)
        {
            const SDL_FRect weaponCol = entityColAABB(
                weapon.base,
                entityIndex,
                collisionIndex);
            if (SDL_HasRectIntersectionFloat(&weaponCol, &targetCol))
            {
                targetHit = true;
                break;
            }
        }
        if (!targetHit)
            continue;

        if (target.type[entityIndex] != EntityType::Player &&
            target.type[entityIndex] != EntityType::NPC)
            continue;

        const uint32_t targetId =
            static_cast<uint32_t>(target.id[entityIndex]);
        if (target.type[entityIndex] == EntityType::Player)
        {
            applyAttackDamage(
                ctx,
                target.type[entityIndex],
                targetId,
                ctx.data.player.statistics,
                ctx.data.player.group,
                ctx.data.player.base,
                NPC_MELEE_AUTO_ATTACK_DAMAGE,
                NPC_MELEE_AUTO_ATTACK_DAMAGE_RANDOM_RANGE);
        }
        else if (target.type[entityIndex] == EntityType::NPC)
        {
            applyAttackDamage(
                ctx,
                target.type[entityIndex],
                targetId,
                ctx.data.npc.statistics,
                ctx.data.npc.group,
                ctx.data.npc.base,
                NPC_MELEE_AUTO_ATTACK_DAMAGE,
                NPC_MELEE_AUTO_ATTACK_DAMAGE_RANDOM_RANGE);
        }
        else
            continue;

        npc.autoAttack.hitTimer[entityIndex] = NPC_MELEE_AUTO_ATTACK_DELAY;
    }
}
