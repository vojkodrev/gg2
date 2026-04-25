#include "RunAStar.h"
#include "../../../../structs/core/Context.h"
#include "heap/HeapPush.h"
#include "heap/HeapPop.h"
#include "heap/HeapEmpty.h"
#include "cost/AStarH.h"
#include "cost/AStarD.h"
#include "neighbors/GetNeighbors.h"
#include "goal/IsGoalReached.h"
#include "reconstruct/ReconstructPath.h"
#include "../../../../utils/hashmap/HashMapInsert.h"
#include "../../../../utils/hashmap/HashMapInsertVoid.h"
#include "../../../../utils/hashmap/HashMapContains.h"
#include "../../../../utils/hashmap/HashMapTryGet.h"

static const int MAX_NEIGHBORS = 8;

bool runAStar(AStarContext& astar, Context& ctx,
              int startNode, float goalX, float goalY, const SDL_FRect& col, int speed)
{
    SpatialHash colHashSnapshot = ctx.collision.spatialHash;

    astar.pathLen = 0;

    float h = astarH(astar, startNode, goalX, goalY);
    hashMapInsert(astar.gscores,  startNode, astar.generation, 0.0f);
    heapPush(astar.heap, startNode, h);

    while (!heapEmpty(astar.heap))
    {
        int current = heapPop(astar.heap);

        if (hashMapContains(astar.closed, current, astar.generation))
            continue;
        hashMapInsert(astar.closed, current, astar.generation);

        if (isGoalReached(astar, col, current))
        {
            reconstructPath(astar, current);
            return true;
        }

        int neighbors[MAX_NEIGHBORS];
        int count = getNeighbors(astar, colHashSnapshot, ctx.data.object, current, speed, neighbors);

        float gCurrent;
        if (!hashMapTryGet(astar.gscores, current, astar.generation, gCurrent))
            continue;

        for (int i = 0; i < count; i++)
        {
            int nb = neighbors[i];
            if (hashMapContains(astar.closed, nb, astar.generation))
                continue;

            float tentativeG = gCurrent + astarD(current, nb, speed);

            float existingG;
            if (hashMapTryGet(astar.gscores, nb, astar.generation, existingG) &&
                tentativeG >= existingG)
                continue;

            hashMapInsert(astar.gscores,  nb, astar.generation, tentativeG);
            hashMapInsert(astar.cameFrom, nb, astar.generation, current);
            heapPush(astar.heap, nb, tentativeG + astarH(astar, nb, goalX, goalY));
        }
    }

    return false;
}
