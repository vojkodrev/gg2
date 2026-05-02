#include "RequestAStarPath.h"
#include "../../../../structs/gameplay/ai/AStarStatus.h"
#include "../../../../structs/npc/NPCPathStatus.h"
#include "pool/AStarAlloc.h"
#include "pool/AStarFree.h"
#include "RunAStar.h"
#include "node/AStarDecode.h"
#include "../../../../utils/Defer.h"
#include <future>

void requestAStarPath(Context& ctx, int npcIndex,
                      const SDL_FRect& destCol)
{
    NPCAi& npcAi = ctx.data.npc.ai;

    npcAi.pathStatus[npcIndex].store(NPCPathStatus::PATH_REQUESTED, std::memory_order_relaxed);

    int astarIndex = astarAlloc(ctx.astarPool);
    if (astarIndex == -1)
        return;

    AStarContext& astar = ctx.astarPool.ctx[astarIndex];
    astar.status.store(AStarStatus::STARTED, std::memory_order_relaxed);

    astar.future = std::async(std::launch::async, [&ctx, &astar, astarIndex, npcIndex, destCol]()
    {
        defer(astarFree(ctx.astarPool, astarIndex));

        NPCAi& npcAi = ctx.data.npc.ai;
        npcAi.pathStatus[npcIndex].store(NPCPathStatus::WAITING_FOR_PATH, std::memory_order_relaxed);

        int pathBuffer[ASTAR_MAX_PATH];
        int length = runAStar(astar, ctx, npcIndex, destCol, pathBuffer);

        if (length > 0)
        {
            for (int i = 0; i < length; i++)
            {
                SDL_Point p = astarDecode(astar, pathBuffer[i]);
                npcAi.path.x[npcIndex][i] = p.x;
                npcAi.path.y[npcIndex][i] = p.y;
            }
            npcAi.pathLength[npcIndex] = (uint32_t)length;
            npcAi.pathIndex[npcIndex]  = 0;
            // release: guarantees path data writes above are visible to main thread on acquire load
            npcAi.pathStatus[npcIndex].store(NPCPathStatus::CALCULATION_FINISHED, std::memory_order_release);
        }
        else
        {
            npcAi.pathStatus[npcIndex].store(NPCPathStatus::CALCULATION_FAILED, std::memory_order_relaxed);
        }
    });
}
