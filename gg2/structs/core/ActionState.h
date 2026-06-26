#pragma once

struct ActionState
{
    bool tabReleased = false;
    bool digit1Released = false;
    bool mouseLeftReleased = false;

    bool prevTabDown = false;
    bool prevDigit1Down = false;
    bool prevMouseLeftDown = false;
};
