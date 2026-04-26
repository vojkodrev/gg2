#pragma once

enum class AStarStatus
{
    IDLE,
    STARTED,
    CALCULATING_PATH,
    FINISHED_CALCULATING,
    COPYING_PATH,
    PATH_READY,
    PATH_NOT_FOUND
};
