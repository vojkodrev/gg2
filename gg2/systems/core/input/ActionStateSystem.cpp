#include "ActionStateSystem.h"

void actionStateSystem(Context &ctx)
{
    auto &action = ctx.data.action;
    const bool digit1Down = ctx.keyboard.digit1;

    action.digit1Released = action.prevDigit1Down && !digit1Down;
    action.prevDigit1Down = digit1Down;
}
