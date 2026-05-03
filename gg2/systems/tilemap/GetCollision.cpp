#include "GetCollision.h"

SDL_FRect getCollision(const tmx::Tileset &tileset, uint32_t tileIdx)
{
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        auto &objs = tile.objectGroup.getObjects();
        if (!objs.empty())
        {
            auto &aabb = objs[0].getAABB();
            return { aabb.left, aabb.top, aabb.width, aabb.height };
        }
        return { 0.0f, 0.0f, 0.0f, 0.0f };
    }
    return { 0.0f, 0.0f, 0.0f, 0.0f };
}
