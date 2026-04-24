#include "IsBlocked.h"
#include "EntityAABB.h"
#include "ColId.h"
#include <SDL3/SDL.h>

bool isBlocked(const SpatialHash& hash, const Object& object, int wx, int wy)
{
    uint16_t candidates[SpatialHash::MAX_PER_BUCKET * 4];
    int n = hash.query((float)wx, (float)wy, 1.0f, 1.0f,
                       candidates, SpatialHash::MAX_PER_BUCKET * 4);

    SDL_FPoint p = { (float)wx, (float)wy };

    for (int i = 0; i < n; i++)
    {
        uint16_t id = candidates[i];
        if (!colIdIsObject(id))
            continue;

        SDL_FRect box = entityColAABB(object, colIdObjectIndex(id));

        if (SDL_PointInRectFloat(&p, &box))
            return true;
    }
    return false;
}
