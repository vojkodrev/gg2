#include "FormatDebugFrameTime.h"
#include "FormatDebugTime.h"
#include <string>

std::string formatDebugFrameTime(float frameTime)
{
    const float fps = frameTime > 0.0f ? 1000.0f / frameTime : 0.0f;
    return formatDebugTime(frameTime) + " (" + formatDebugTime(fps) + ")";
}
