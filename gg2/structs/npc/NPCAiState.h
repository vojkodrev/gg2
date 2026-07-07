#pragma once

enum class NPCAiState : int
{
    Idle,
    Patrolling,
    PursuingTarget,
    PursueTarget,
    Attack,
    ReturnToSpawn
};
