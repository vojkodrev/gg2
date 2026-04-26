#pragma once

enum class NPCPathStatus
{
    IDLE,
    STARTED,
    WAITING_FOR_PATH,
    CALCULATION_FINISHED,
    WALKING,
    FINISHED_WALKING
};
