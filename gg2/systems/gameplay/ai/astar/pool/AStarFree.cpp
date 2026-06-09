#include "AStarFree.h"
#include "../../../../utils/pool/PoolFree.h"
#include "../../../../structs/gameplay/ai/AStarStatus.h"

void astarFree(AStarPool& pool, int index)
{
    pool.ctx[index].status.store(AStarStatus::IDLE, std::memory_order_relaxed);
    poolFree(pool.pool, index);
}
