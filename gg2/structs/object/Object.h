#pragma once
#include <cstdint>
#include "../core/SpriteSrc.h"
#include "../core/EntityPosition.h"
#include "../core/EntityCollision.h"
#include "../core/Constants.h"

struct Object
{
    uint32_t objectCount;
    SpriteSrc<MAX_OBJECTS> src;
    EntityPosition<MAX_OBJECTS> position;
    EntityCollision<MAX_OBJECTS> collision;
};
