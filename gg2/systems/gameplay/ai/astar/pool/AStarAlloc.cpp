#include "AStarAlloc.h"
#include "AStarConstants.h"
#include "../../../../utils/queue/QueueEmpty.h"
#include "../../../../utils/queue/QueueDequeue.h"
#include "../../../../structs/gameplay/ai/AStarStatus.h"

int astarAlloc(AStarPool& pool)
{
    int index = -1;

    if (!queueEmpty(pool.freeQueue))
        index = queueDequeue(pool.freeQueue);
    else if (pool.count < MAX_ASTARS)
        index = pool.count++;

    if (index != -1)
        pool.ctx[index].status.store(AStarStatus::IDLE, std::memory_order_relaxed);

    return index;
}
