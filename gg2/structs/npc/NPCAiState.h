#pragma once

enum class NPCAiState : int
{
    Idle,
    FollowPlayer,
    Patrolling,
    PursueTarget,
    Attack,
    ReturnToSpawn
};
