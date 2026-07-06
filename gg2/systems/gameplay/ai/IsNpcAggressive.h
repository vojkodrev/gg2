#pragma once
#include "../../../structs/npc/NPCAi.h"
#include <cstdint>

inline bool isNpcAggressive(const NPCAi &ai, uint32_t i)
{
    return
        ai.state[i] == NPCAiState::PursuingTarget ||
        ai.state[i] == NPCAiState::PursueTarget ||
        ai.state[i] == NPCAiState::Attack;
}
