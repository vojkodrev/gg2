#include "GetAnchors.h"

uint32_t getAnchors(
    const tmx::Tileset &tileset,
    uint32_t tileIdx,
    const char *name,
    SDL_FRect *anchors,
    uint32_t maxAnchors)
{
    uint32_t count = 0;
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;

        for (auto &obj : tile.objectGroup.getObjects())
        {
            if (obj.getName() != name || count >= maxAnchors)
                continue;

            const auto &aabb = obj.getAABB();
            anchors[count++] = {
                aabb.left,
                aabb.top,
                aabb.width,
                aabb.height
            };
        }
        break;
    }
    return count;
}
