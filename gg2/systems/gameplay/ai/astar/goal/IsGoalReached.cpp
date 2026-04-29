#include "IsGoalReached.h"
#include "../node/AStarDecode.h"
#include <SDL3/SDL.h>

bool isGoalReached(const AStarContext& astar, const SDL_FRect& col, int node)
{
    SDL_Point p;
    astarDecode(astar, node, p);
    SDL_FPoint fp = { (float)p.x, (float)p.y };
    return SDL_PointInRectFloat(&fp, &col);
}
