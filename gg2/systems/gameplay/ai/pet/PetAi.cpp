#include "PetAi.h"
#include "PetIdle.h"
#include "PetFollowPlayer.h"
#include "PetPursueTarget.h"
#include "PetAttack.h"

void petAi(uint32_t n, Context &ctx)
{
    auto &ai = ctx.data.npc.ai;

    switch (ai.state[n])
    {
    case NPCAiState::Idle:         petIdle(n, ctx);            break;
    case NPCAiState::FollowPlayer: petFollowPlayer(n, ctx);    break;
    case NPCAiState::PursueTarget: petPursueTarget(n, ctx);    break;
    case NPCAiState::Attack:       petAttack(n, ctx);          break;
    default: break;
    }
}
