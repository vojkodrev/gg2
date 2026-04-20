#include "GetCollision.h"

void GetCollision(const tmx::Tileset &tileset, uint32_t tileIdx, float &offX, float &offY, float &w, float &h)
{
    for (auto &tile : tileset.getTiles())
    {
        if (tile.ID != tileIdx)
            continue;
        auto &objs = tile.objectGroup.getObjects();
        if (!objs.empty())
        {
            auto &aabb = objs[0].getAABB();
            offX = aabb.left;
            offY = aabb.top;
            w = aabb.width;
            h = aabb.height;
        }
        return;
    }
}
