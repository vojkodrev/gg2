#include "AStarFree.h"
#include "../../../../utils/queue/QueueEnqueue.h"
#include "../../../../structs/gameplay/ai/AStarStatus.h"

void astarFree(AStarPool& pool, int index)
{
    pool.ctx[index].status = AStarStatus::IDLE;
    queueEnqueue(pool.freeQueue, index);
}
