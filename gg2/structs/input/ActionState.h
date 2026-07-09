#pragma once

struct ActionState
{
    bool tabReleased = false;
    bool digit1Released = false;
    bool digit2Released = false;
    bool digit3Released = false;
    bool digit4Released = false;
    bool digit5Released = false;
    bool mouseLeftReleased = false;

    bool prevTabDown = false;
    bool prevDigit1Down = false;
    bool prevDigit2Down = false;
    bool prevDigit3Down = false;
    bool prevDigit4Down = false;
    bool prevDigit5Down = false;
    bool prevMouseLeftDown = false;
};
