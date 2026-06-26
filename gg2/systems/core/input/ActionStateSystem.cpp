#include "ActionStateSystem.h"

void actionStateSystem(Context &ctx)
{
    auto &action = ctx.data.action;
    const bool digit1Down = ctx.keyboard.digit1;
    const bool mouseLeftDown = ctx.mouse.leftClicked;

    action.digit1Released = action.prevDigit1Down && !digit1Down;
    action.mouseLeftReleased = action.prevMouseLeftDown && !mouseLeftDown;

    action.prevDigit1Down = digit1Down;
    action.prevMouseLeftDown = mouseLeftDown;
}
