#include "FillPlayerRenderBuffer.h"
#include "FillEntityBaseRenderBuffer.h"
#include "FillEquipmentRenderBuffer.h"
#include "FillHealthbarRenderBuffer.h"
#include "FillManabarRenderBuffer.h"

void fillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &player = ctx.data.player;
    fillEntityBaseRenderBuffer(
        rb,
        player.base,
        0,
        player.group.id[0],
        player.zIndex[0]);

    fillEquipmentRenderBuffer(rb, player.equipment, 0, player.group.id[0]);
    fillHealthbarRenderBuffer(rb, player.healthbar, 0, player.group.id[0]);
    fillManabarRenderBuffer(rb, player.manabar, 0, player.group.id[0]);
}
