#include "GetAnchor.h"

bool getAnchor(
    const tmx::Tileset &tileset,
    uint32_t tileIdx,
    const char *name,
    SDL_FRect &anchor)
{
    anchor = {};
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        auto &objs = tile.objectGroup.getObjects();
        for (auto &obj : objs)
        {
            if (obj.getName() != name)
                continue;
            auto &aabb = obj.getAABB();
            anchor = {aabb.left, aabb.top, aabb.width, aabb.height};
            return true;
        }
        return false;
    }
    return false;
}
