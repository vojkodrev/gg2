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
    const bool modifierDown =
        ctx.keyboard.ctrl || ctx.keyboard.alt || ctx.keyboard.shift;

    const bool digit1Modified =
        action.digit1Modified || (digit1Down && modifierDown);
    const bool digit2Modified =
        action.digit2Modified || (digit2Down && modifierDown);
    const bool digit3Modified =
        action.digit3Modified || (digit3Down && modifierDown);
    const bool digit4Modified =
        action.digit4Modified || (digit4Down && modifierDown);
    const bool digit5Modified =
        action.digit5Modified || (digit5Down && modifierDown);

    action.tabReleased = action.prevTabDown && !tabDown;
    action.digit1Released =
        action.prevDigit1Down && !digit1Down && !digit1Modified;
    action.digit2Released =
        action.prevDigit2Down && !digit2Down && !digit2Modified;
    action.digit3Released =
        action.prevDigit3Down && !digit3Down && !digit3Modified;
    action.digit4Released =
        action.prevDigit4Down && !digit4Down && !digit4Modified;
    action.digit5Released =
        action.prevDigit5Down && !digit5Down && !digit5Modified;
    action.mouseLeftReleased = action.prevMouseLeftDown && !mouseLeftDown;

    action.prevTabDown = tabDown;
    action.prevDigit1Down = digit1Down;
    action.prevDigit2Down = digit2Down;
    action.prevDigit3Down = digit3Down;
    action.prevDigit4Down = digit4Down;
    action.prevDigit5Down = digit5Down;
    action.digit1Modified = digit1Down && digit1Modified;
    action.digit2Modified = digit2Down && digit2Modified;
    action.digit3Modified = digit3Down && digit3Modified;
    action.digit4Modified = digit4Down && digit4Modified;
    action.digit5Modified = digit5Down && digit5Modified;
    action.prevMouseLeftDown = mouseLeftDown;
}
