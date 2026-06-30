#include "ShowBarSystem.h"
#include <cstdint>

void showBarSystem(Context &ctx)
{
    const bool showPlayerBars =
        ctx.data.player.statistics.health.hp[0] < ctx.data.player.statistics.health.maxHp[0] ||
        ctx.data.player.statistics.mana.mana[0] < ctx.data.player.statistics.mana.maxMana[0];
    ctx.data.player.healthbar.show[0] = showPlayerBars;
    ctx.data.player.manabar.show[0] = showPlayerBars;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        ctx.data.npc.healthbar.show[i] =
            ctx.data.npc.statistics.health.hp[i] < ctx.data.npc.statistics.health.maxHp[i];
    }
}
