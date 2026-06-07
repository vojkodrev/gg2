#include "RunPetAi.h"
#include "HandlePetIdle.h"
#include "HandlePetFollowPlayer.h"

void runPetAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:       handlePetIdle(n, ctx);        break;
    case NPCAiState::GoToPlayer: handlePetFollowPlayer(n, ctx);  break;
    default:                     break;
    }
}
