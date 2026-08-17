#include "DebugRenderRangedDeadZone.h"
#include "MainEntityColAABB.h"
#include "EntityColCenter.h"
#include "RenderMonsterAggroRange.h"
#include "RenderNpcTargetVisibleLine.h"
#include "RenderPlayerTargetVisibleLine.h"
#include "RenderRangedDeadZone.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../structs/npc/NPCAiType.h"

void debugRenderRangedDeadZone(const Context &ctx)
{
    if (!ctx.data.debug.showRangedDeadZone)
        return;

    SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);

    const auto &player = ctx.data.player;
    if (player.equipment.weapon.type[0] == WeaponType::Ranged)
    {
        renderRangedDeadZone(
            ctx,
            entityColCenter(mainEntityColAABB(player.base, 0)));

        if (player.autoAttack.active[0] && player.targetVisible)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 0, 255, 255, 255);
            renderPlayerTargetVisibleLine(ctx);
        }
    }

    const auto &npc = ctx.data.npc;
    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!npc.active[entityIndex])
            continue;

        const SDL_FPoint npcCenter =
            entityColCenter(mainEntityColAABB(npc.base, entityIndex));
        if (npc.ai.type[entityIndex] == NPCAiType::MonsterMelee ||
            npc.ai.type[entityIndex] == NPCAiType::MonsterRanged)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderMonsterAggroRange(ctx, npcCenter);
        }

        if (npc.ai.type[entityIndex] == NPCAiType::MonsterRanged &&
            npc.equipment.weapon.type[entityIndex] == WeaponType::Ranged)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderRangedDeadZone(
                ctx,
                npcCenter);

            if (npc.ai.targetVisible[entityIndex])
            {
                SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
                renderNpcTargetVisibleLine(ctx, entityIndex);
            }
        }
    }
}
