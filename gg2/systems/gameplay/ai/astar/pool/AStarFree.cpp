#include "AStarFree.h"
#include "QueueEnqueue.h"
#include "../../../../structs/gameplay/ai/AStarStatus.h"

void astarFree(AStarPool& pool, int index)
{
    pool.ctx[index].status = AStarStatus::IDLE;
    queueEnqueue(pool, index);
}
