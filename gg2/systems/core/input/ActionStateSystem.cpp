#include "ActionStateSystem.h"

void actionStateSystem(Context &ctx)
{
    auto &action = ctx.data.action;
    const bool tabDown = ctx.keyboard.tab;
    const bool digit1Down = ctx.keyboard.digit1;
    const bool mouseLeftDown = ctx.mouse.leftClicked;

    action.tabReleased = action.prevTabDown && !tabDown;
    action.digit1Released = action.prevDigit1Down && !digit1Down;
    action.mouseLeftReleased = action.prevMouseLeftDown && !mouseLeftDown;

    action.prevTabDown = tabDown;
    action.prevDigit1Down = digit1Down;
    action.prevMouseLeftDown = mouseLeftDown;
}
