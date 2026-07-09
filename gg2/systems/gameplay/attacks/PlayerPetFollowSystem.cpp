#include "PlayerPetFollowSystem.h"
#include "../ai/SetNpcAiStateFollowPlayer.h"

void playerPetFollowSystem(Context &ctx)
{
    if (!ctx.data.action.digit5Released)
        return;

    const int petId = ctx.data.player.petId;
    if (petId == -1)
        return;

    ctx.data.npc.autoAttack.active[petId] = false;
    setNpcAiStateFollowPlayer((uint32_t)petId, ctx);
}
