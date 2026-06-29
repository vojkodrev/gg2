#include "AStarFree.h"
#include "../../../../utils/pool/PoolFree.h"
#include "../../../../structs/ai/AStarStatus.h"

void astarFree(AStarPool& pool, int index)
{
    pool.ctx.status[index].store(AStarStatus::IDLE, std::memory_order_relaxed);
    poolFree(pool.pool, index);
}
