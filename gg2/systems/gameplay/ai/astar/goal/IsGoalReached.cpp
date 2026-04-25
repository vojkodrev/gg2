#include "IsGoalReached.h"
#include "../node/AStarDecode.h"
#include <SDL3/SDL.h>

bool isGoalReached(const AStarContext& astar, const SDL_FRect& col, int node)
{
    int x, y;
    astarDecode(astar, node, x, y);
    SDL_FPoint point = {(float)x, (float)y};
    return SDL_PointInRectFloat(&point, &col);
}
