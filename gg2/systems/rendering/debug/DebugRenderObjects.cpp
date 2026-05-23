#include "DebugRenderObjects.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABBObject.h"

void debugRenderObjects(const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_Renderer *renderer = ctx.renderer;
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        renderColBox(renderer, entityColAABB(ctx.data.object, i), off, screen);
}
