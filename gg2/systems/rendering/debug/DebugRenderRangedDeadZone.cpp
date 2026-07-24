#include "DebugRenderRangedDeadZone.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "RenderMonsterAggroRange.h"
#include "RenderNpcTargetVisibleLine.h"
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
        renderRangedDeadZone(
            ctx,
            entityColCenter(entityColAABB(player.base, 0)));

    const auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;

        const SDL_FPoint npcCenter =
            entityColCenter(entityColAABB(npc.base, i));
        if (npc.ai.type[i] == NPCAiType::MonsterMelee ||
            npc.ai.type[i] == NPCAiType::MonsterRanged)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 255);
            renderMonsterAggroRange(ctx, npcCenter);
        }

        if (npc.equipment.weapon.type[i] == WeaponType::Ranged)
        {
            SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);
            renderRangedDeadZone(
                ctx,
                npcCenter);

            if (npc.equipment.weapon.showAmmo[i] && npc.ai.targetVisible[i])
                renderNpcTargetVisibleLine(ctx, i);
        }
    }
}
