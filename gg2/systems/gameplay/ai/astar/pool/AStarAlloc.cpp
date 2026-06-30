#include "AStarAlloc.h"
#include "AStarConstants.h"
#include "../../../../utils/pool/PoolAlloc.h"
#include "../../../../structs/ai/AStarStatus.h"

int astarAlloc(AStarPool& pool)
{
    int index = poolAlloc(pool.pool);

    if (index != -1)
        pool.ctx.status[index].store(AStarStatus::IDLE, std::memory_order_relaxed);

    return index;
}
