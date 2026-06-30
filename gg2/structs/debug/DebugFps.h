#pragma once
#include "../core/constants/DebugConstants.h"
#include "../../utils/queue/Queue.h"

struct DebugFps
{
    int groupId = -1;
    Queue<int, DEBUG_FPS_DIGIT_EFFECT_QUEUE_SIZE> digitEffectIds = {};
};
