#include "AStarFree.h"
#include "../../../../utils/pool/PoolFree.h"
#include "../../../../structs/ai/AStarStatus.h"

void astarFree(AStarPool& pool, int index)
{
    if (!pool.pool.active[0][index])
        return;

    pool.ctx.status[index].store(AStarStatus::IDLE, std::memory_order_relaxed);
    poolFree(pool.pool, 0, index);
}
