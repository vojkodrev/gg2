#include "PlayerPetAttackSystem.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../ai/ClearNpcAiTarget.h"
#include "../ai/SetNpcAiStateFollowPlayer.h"
#include "../ai/SetNpcAiStatePursueTarget.h"
#include "../ai/SetNpcAiTarget.h"
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
        setNpcAiStateFollowPlayer((uint32_t)petId, ctx);
        clearNpcAiTarget((uint32_t)petId, ctx);
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

    setNpcAiStatePursueTarget(ctx, (uint32_t)petId);
    setNpcAiTarget((uint32_t)petId, ctx, EntityType::NPC, targetId);
}
