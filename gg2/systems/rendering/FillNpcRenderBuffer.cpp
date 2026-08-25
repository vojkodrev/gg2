#include "FillNpcRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "FillEquipmentRenderBuffer.h"
#include "FillHealthbarRenderBuffer.h"
#include "FillManabarRenderBuffer.h"

void fillNpcRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &npc = ctx.data.npc;
    for (uint32_t npcIndex = 0; npcIndex < MAX_NPCS; npcIndex++)
    {
        if (!npc.active[npcIndex])
            continue;

        fillEntityBaseRenderBuffer(
            rb,
            npc.base,
            npcIndex,
            npc.group.id[npcIndex],
            npc.zIndex[npcIndex]);

        fillEquipmentRenderBuffer(
            rb,
            npc.equipment,
            npcIndex,
            npc.group.id[npcIndex]);
        fillHealthbarRenderBuffer(
            rb,
            npc.healthbar,
            npcIndex,
            npc.group.id[npcIndex]);
        fillManabarRenderBuffer(
            rb,
            npc.manabar,
            npcIndex,
            npc.group.id[npcIndex]);
    }
}
