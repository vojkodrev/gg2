#include "FillNpcRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "FillEquipmentRenderBuffer.h"
#include "FillHealthbarRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillNpcRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i])
            continue;

        int groupId = npc.group.id[i];
        fillEntityBaseRenderBuffer(
            rb,
            npc.base,
            i,
            groupId,
            PARENT_Z_INDEX);

        fillEquipmentRenderBuffer(rb, npc.equipment, i, groupId);
        fillHealthbarRenderBuffer(rb, npc.healthbar, i, groupId);
    }
}
