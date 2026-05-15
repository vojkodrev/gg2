#include "UpdatePet.h"
#include "UpdatePetIdle.h"
#include "UpdatePetGoToPlayer.h"

void updatePet(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:       updatePetIdle(n, ctx);        break;
    case NPCAiState::GoToPlayer: updatePetGoToPlayer(n, ctx);  break;
    default:                     break;
    }
}
