#pragma once

enum class FacingDirection
{
    Left,
    Right
};

template<int N>
struct Facing
{
    FacingDirection facing[N];
    FacingDirection initialFacing[N];
    bool flipX[N];
};
