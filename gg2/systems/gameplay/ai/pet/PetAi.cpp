#include "PetAi.h"
#include "PetIdle.h"
#include "PetFollowPlayer.h"

void petAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:         petIdle(n, ctx);         break;
    case NPCAiState::FollowPlayer: petFollowPlayer(n, ctx); break;
    default: break;
    }
}
