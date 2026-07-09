#pragma once

enum class NPCAiState : int
{
    Idle,
    FollowPlayer,
    Patrolling,
    PursuingTarget,
    PursueTarget,
    Attack,
    ReturnToSpawn
};
