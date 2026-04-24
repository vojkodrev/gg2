#include "AStarD.h"

float astarD(int fromNode, int toNode, int speed)
{
    int dx = (toNode % ASTAR_SEARCH_D) - (fromNode % ASTAR_SEARCH_D);
    int dy = (toNode / ASTAR_SEARCH_D) - (fromNode / ASTAR_SEARCH_D);
    return ((dx != 0 && dy != 0) ? 1.4142135f : 1.0f) * speed;
}
