#include "NpcTabSelectSystem.h"
#include "../../../../structs/npc/NPCAiType.h"

void npcTabSelectSystem(Context &ctx)
{
    if (!ctx.data.action.tabReleased)
        return;

    const int currentNpc = ctx.data.player.selectedNpc;
    ctx.data.player.previousSelectedNpc = currentNpc;
    ctx.data.player.selectedNpc = -1;

    for (int step = 1; step <= MAX_NPCS; step++)
    {
        const int i = (currentNpc + step + MAX_NPCS) % MAX_NPCS;
        if (!ctx.data.npc.active[i])
            continue;
        if (ctx.data.npc.ai.type[i] == NPCAiType::Pet)
            continue;

        ctx.data.player.selectedNpc = i;
        return;
    }
}
