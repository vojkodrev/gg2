#pragma once
#include <cstdint>
#include "ObjectSrc.h"
#include "ObjectPosition.h"
#include "ObjectCollision.h"

struct Object
{
    uint32_t objectCount;
    ObjectSrc src;
    ObjectPosition position;
    ObjectCollision collision;
};
