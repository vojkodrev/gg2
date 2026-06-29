#include "DebugStateSystem.h"

void debugStateSystem(Context &ctx)
{
    const bool ctrlAlt = ctx.keyboard.ctrl && ctx.keyboard.alt;
    auto &debug = ctx.data.debug;

    const bool ctrlAltFDown = ctrlAlt && ctx.keyboard.f;
    const bool ctrlAlt0Down = ctrlAlt && ctx.keyboard.digit0;
    const bool ctrlAlt1Down = ctrlAlt && ctx.keyboard.digit1;
    const bool ctrlAlt2Down = ctrlAlt && ctx.keyboard.digit2;
    const bool ctrlAlt3Down = ctrlAlt && ctx.keyboard.digit3;
    const bool ctrlAlt4Down = ctrlAlt && ctx.keyboard.digit4;
    const bool ctrlAlt5Down = ctrlAlt && ctx.keyboard.digit5;

    if (debug.prevCtrlAltFDown && !ctrlAltFDown)
        debug.showFps = !debug.showFps;

    if (debug.prevCtrlAlt0Down && !ctrlAlt0Down)
    {
        const bool nextShow = !debug.showNavigation;
        debug.showFps = nextShow;
        debug.showNavigation = nextShow;
        debug.showCollision = nextShow;
        debug.showWeaponCollision = nextShow;
        debug.showAmmoCollision = nextShow;
        debug.showEffectCollision = nextShow;
    }

    if (debug.prevCtrlAlt1Down && !ctrlAlt1Down)
        debug.showNavigation = !debug.showNavigation;

    if (debug.prevCtrlAlt2Down && !ctrlAlt2Down)
        debug.showCollision = !debug.showCollision;

    if (debug.prevCtrlAlt3Down && !ctrlAlt3Down)
        debug.showWeaponCollision = !debug.showWeaponCollision;

    if (debug.prevCtrlAlt4Down && !ctrlAlt4Down)
        debug.showAmmoCollision = !debug.showAmmoCollision;

    if (debug.prevCtrlAlt5Down && !ctrlAlt5Down)
        debug.showEffectCollision = !debug.showEffectCollision;

    debug.prevCtrlAltFDown = ctrlAltFDown;
    debug.prevCtrlAlt0Down = ctrlAlt0Down;
    debug.prevCtrlAlt1Down = ctrlAlt1Down;
    debug.prevCtrlAlt2Down = ctrlAlt2Down;
    debug.prevCtrlAlt3Down = ctrlAlt3Down;
    debug.prevCtrlAlt4Down = ctrlAlt4Down;
    debug.prevCtrlAlt5Down = ctrlAlt5Down;
}
