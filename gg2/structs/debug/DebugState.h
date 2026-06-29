#pragma once

struct DebugState
{
    bool showFps = false;
    bool showNavigation = false;
    bool showCollision = false;
    bool showWeaponCollision = false;
    bool showAmmoCollision = false;
    bool showEffectCollision = false;

    bool prevCtrlAltFDown = false;
    bool prevCtrlAlt0Down = false;
    bool prevCtrlAlt1Down = false;
    bool prevCtrlAlt2Down = false;
    bool prevCtrlAlt3Down = false;
    bool prevCtrlAlt4Down = false;
    bool prevCtrlAlt5Down = false;
};
