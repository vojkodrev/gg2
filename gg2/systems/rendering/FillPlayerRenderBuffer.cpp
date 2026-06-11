#include "FillPlayerRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "equipment/FillEquipmentRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &player = ctx.data.player;
    uint32_t n = fillEntityBaseRenderBuffer(
        rb,
        player.base,
        0,
        player.groupId,
        PARENT_Z_INDEX);

    fillEquipmentRenderBuffer(rb, player.equipment, 0, n, player.groupId);
}
