#pragma once

struct ActionState
{
    bool digit1Released = false;
    bool mouseLeftReleased = false;

    bool prevDigit1Down = false;
    bool prevMouseLeftDown = false;
};
