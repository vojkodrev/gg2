#include "ObjectDepthSystem.h"
#include "SetEntityBaseDepthY.h"
#include <cstdint>

void objectDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        setEntityBaseDepthY(ctx.data.object.base, i);
}
