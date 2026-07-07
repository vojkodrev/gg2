#include "ActionStateSystem.h"

void actionStateSystem(Context &ctx)
{
    auto &action = ctx.data.action;
    const bool tabDown = ctx.keyboard.tab;
    const bool digit1Down = ctx.keyboard.digit1;
    const bool digit2Down = ctx.keyboard.digit2;
    const bool digit3Down = ctx.keyboard.digit3;
    const bool digit4Down = ctx.keyboard.digit4;
    const bool digit5Down = ctx.keyboard.digit5;
    const bool mouseLeftDown = ctx.mouse.leftClicked;

    action.tabReleased = action.prevTabDown && !tabDown;
    action.digit1Released = action.prevDigit1Down && !digit1Down;
    action.digit2Released = action.prevDigit2Down && !digit2Down;
    action.digit3Released = action.prevDigit3Down && !digit3Down;
    action.digit4Released = action.prevDigit4Down && !digit4Down;
    action.digit5Released = action.prevDigit5Down && !digit5Down;
    action.mouseLeftReleased = action.prevMouseLeftDown && !mouseLeftDown;

    action.prevTabDown = tabDown;
    action.prevDigit1Down = digit1Down;
    action.prevDigit2Down = digit2Down;
    action.prevDigit3Down = digit3Down;
    action.prevDigit4Down = digit4Down;
    action.prevDigit5Down = digit5Down;
    action.prevMouseLeftDown = mouseLeftDown;
}
