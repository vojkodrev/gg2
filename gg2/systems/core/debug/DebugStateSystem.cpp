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

    if (debug.ctrlAltFArmed && !ctrlAltFDown)
    {
        debug.showFps = !debug.showFps;
        debug.ctrlAltFArmed = false;
    }

    if (debug.ctrlAlt0Armed && !ctrlAlt0Down)
    {
        const bool nextShow = !debug.showNavigation;
        debug.showFps = nextShow;
        debug.showNavigation = nextShow;
        debug.showCollision = nextShow;
        debug.showWeaponCollision = nextShow;
        debug.showAmmoCollision = nextShow;
        debug.showEffectCollision = nextShow;
        debug.ctrlAlt0Armed = false;
    }

    if (debug.ctrlAlt1Armed && !ctrlAlt1Down)
    {
        debug.showNavigation = !debug.showNavigation;
        debug.ctrlAlt1Armed = false;
    }

    if (debug.ctrlAlt2Armed && !ctrlAlt2Down)
    {
        debug.showCollision = !debug.showCollision;
        debug.ctrlAlt2Armed = false;
    }

    if (debug.ctrlAlt3Armed && !ctrlAlt3Down)
    {
        debug.showWeaponCollision = !debug.showWeaponCollision;
        debug.ctrlAlt3Armed = false;
    }

    if (debug.ctrlAlt4Armed && !ctrlAlt4Down)
    {
        debug.showAmmoCollision = !debug.showAmmoCollision;
        debug.ctrlAlt4Armed = false;
    }

    if (debug.ctrlAlt5Armed && !ctrlAlt5Down)
    {
        debug.showEffectCollision = !debug.showEffectCollision;
        debug.ctrlAlt5Armed = false;
    }

    debug.ctrlAltFArmed = debug.ctrlAltFArmed || ctrlAltFDown;
    debug.ctrlAlt0Armed = debug.ctrlAlt0Armed || ctrlAlt0Down;
    debug.ctrlAlt1Armed = debug.ctrlAlt1Armed || ctrlAlt1Down;
    debug.ctrlAlt2Armed = debug.ctrlAlt2Armed || ctrlAlt2Down;
    debug.ctrlAlt3Armed = debug.ctrlAlt3Armed || ctrlAlt3Down;
    debug.ctrlAlt4Armed = debug.ctrlAlt4Armed || ctrlAlt4Down;
    debug.ctrlAlt5Armed = debug.ctrlAlt5Armed || ctrlAlt5Down;
}
