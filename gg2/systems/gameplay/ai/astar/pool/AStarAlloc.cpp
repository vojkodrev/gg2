#include "AStarAlloc.h"
#include "QueueEmpty.h"
#include "QueueDequeue.h"
#include "../../../../structs/gameplay/ai/AStarStatus.h"

int astarAlloc(AStarPool& pool)
{
    int index = -1;

    if (!queueEmpty(pool))
        index = queueDequeue(pool);
    else if (pool.count < MAX_ASTARS)
        index = pool.count++;

    if (index != -1)
        pool.ctx[index].status = AStarStatus::IDLE;

    return index;
}
