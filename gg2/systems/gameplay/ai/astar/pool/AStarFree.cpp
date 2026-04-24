#include "AStarFree.h"
#include "QueueEnqueue.h"

void astarFree(AStarPool& pool, int index)
{
    queueEnqueue(pool, index);
}
