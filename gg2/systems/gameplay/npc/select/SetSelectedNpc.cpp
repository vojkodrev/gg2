#include "SetSelectedNpc.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/npc/NPCAiType.h"

void setSelectedNpc(Context &ctx, int selectedNpc)
{
    ctx.data.player.previousSelectedNpc = ctx.data.player.selectedNpc;
    ctx.data.player.selectedNpc = selectedNpc;

    if (selectedNpc == INVALID_ID)
        ctx.data.player.autoAttack.active[0] = false;
    else if (ctx.data.npc.ai.type[selectedNpc] == NPCAiType::Pet)
        ctx.data.player.autoAttack.active[0] = false;
}
