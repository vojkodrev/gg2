#include "DebugStateSystem.h"

void debugStateSystem(Context &ctx)
{
    const bool ctrlAlt = ctx.keyboard.ctrl && ctx.keyboard.alt;
    auto &debug = ctx.data.debug;

    const bool ctrlAlt1Down = ctrlAlt && ctx.keyboard.digit1;
    const bool ctrlAlt2Down = ctrlAlt && ctx.keyboard.digit2;

    if (debug.prevCtrlAlt1Down && !ctrlAlt1Down)
        debug.showNavigation = !debug.showNavigation;

    if (debug.prevCtrlAlt2Down && !ctrlAlt2Down)
        debug.showCollision = !debug.showCollision;

    debug.prevCtrlAlt1Down = ctrlAlt1Down;
    debug.prevCtrlAlt2Down = ctrlAlt2Down;
}
