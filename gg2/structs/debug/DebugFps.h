#pragma once
#include <SDL3/SDL.h>
#include "../core/constants/DebugConstants.h"
#include "../../utils/queue/Queue.h"

struct DebugFps
{
    int groupId = -1;
    Uint64 astarTime = 0;
    float avgAstarTime = 0.0f;
    float avgFrameTime = 0.0f;
    Queue<int, DEBUG_FPS_CHARACTER_EFFECT_QUEUE_SIZE> characterEffectIds = {};
};
