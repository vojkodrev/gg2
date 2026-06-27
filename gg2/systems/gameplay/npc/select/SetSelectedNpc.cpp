#include "SetSelectedNpc.h"
#include "../../../../structs/npc/NPCAiType.h"

void setSelectedNpc(Context &ctx, int selectedNpc)
{
    ctx.data.player.previousSelectedNpc = ctx.data.player.selectedNpc;
    ctx.data.player.selectedNpc = selectedNpc;

    if (selectedNpc == -1)
        ctx.data.player.autoAttack.active = false;
    else if (ctx.data.npc.ai.type[selectedNpc] == NPCAiType::Pet)
        ctx.data.player.autoAttack.active = false;
}
