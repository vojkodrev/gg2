#include "AStarAlloc.h"
#include "AStarConstants.h"
#include "../../../../utils/pool/PoolAlloc.h"
#include "../../../../structs/ai/AStarStatus.h"

int astarAlloc(AStarPool& pool)
{
    int index = poolAlloc(pool.pool, 0);

    if (index != INVALID_ID)
        pool.ctx.status[index].store(AStarStatus::IDLE, std::memory_order_relaxed);

    return index;
}
