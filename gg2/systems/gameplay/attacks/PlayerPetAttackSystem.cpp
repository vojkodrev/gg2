#include "PlayerPetAttackSystem.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../ai/SetNpcAiStateIdle.h"
#include "../ai/monster/SetNpcAiStatePursueTarget.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"

void playerPetAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit4Released)
        return;

    const int petId = ctx.data.player.petId;
    if (petId == INVALID_ID)
        return;

    auto &petAutoAttackActive = ctx.data.npc.autoAttack.active[petId];
    petAutoAttackActive = !petAutoAttackActive;
    if (!petAutoAttackActive)
    {
        setNpcAiStateIdle((uint32_t)petId, ctx);
        return;
    }

    const int targetId = ctx.data.player.selectedNpc;
    if (targetId == INVALID_ID)
    {
        petAutoAttackActive = false;
        return;
    }
    if (ctx.data.npc.ai.type[targetId] != NPCAiType::Monster)
    {
        petAutoAttackActive = false;
        return;
    }

    setNpcAiStatePursueTarget((uint32_t)petId, ctx, EntityType::NPC, targetId);
}
