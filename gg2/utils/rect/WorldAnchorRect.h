#pragma once
#include <SDL3/SDL.h>

inline SDL_FRect worldAnchorRect(float dstX, float dstY, float dstW, const SDL_FRect &localAnchor, bool flipX)
{
    const float anchorX = flipX ? dstW - localAnchor.x - localAnchor.w : localAnchor.x;
    return {dstX + anchorX, dstY + localAnchor.y, localAnchor.w, localAnchor.h};
}
