#include "BarFrameSystem.h"
#include "SetBarFrame.h"
#include <cstdint>

void barFrameSystem(Context &ctx)
{
    if (ctx.data.player.healthbar.show[0] && ctx.data.player.statistics.health.dirty[0])
        setBarFrame(
            ctx.data.player.healthbar,
            ctx.data.player.statistics.health.hp[0],
            ctx.data.player.statistics.health.maxHp[0],
            0);

    if (ctx.data.player.manabar.show[0] && ctx.data.player.statistics.mana.dirty[0])
        setBarFrame(
            ctx.data.player.manabar,
            ctx.data.player.statistics.mana.mana[0],
            ctx.data.player.statistics.mana.maxMana[0],
            0);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (ctx.data.npc.healthbar.show[i] && ctx.data.npc.statistics.health.dirty[i])
            setBarFrame(
                ctx.data.npc.healthbar,
                ctx.data.npc.statistics.health.hp[i],
                ctx.data.npc.statistics.health.maxHp[i],
                i);
    }
}
