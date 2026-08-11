#include "RequestAStarPath.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/ai/AStarStatus.h"
#include "../../../../structs/npc/NPCPathStatus.h"
#include "pool/AStarAlloc.h"
#include "pool/AStarFree.h"
#include "RunAStar.h"
#include "node/AStarDecode.h"
#include "../../../../utils/Defer.h"
#include <future>

void requestAStarPath(
    Context& ctx, 
    int npcIndex,
    const SDL_FRect& moverBox,
    const SDL_FPoint& moverCenter,
    float moverBoxBuffer,
    const SDL_FRect& destCol,
    int targetNpcIndex,
    bool isPlayerBlocking)
{
    NPCAi& npcAi = ctx.data.npc.ai;

    npcAi.path.status[npcIndex].store(NPCPathStatus::PATH_REQUESTED, std::memory_order_relaxed);

    int astarIndex = astarAlloc(ctx.astarPool);
    if (astarIndex == INVALID_ID)
        return;

    auto& astar = ctx.astarPool.ctx;
    astar.status[astarIndex].store(AStarStatus::STARTED, std::memory_order_relaxed);

    astar.future[astarIndex] = std::async(std::launch::async, [
        &ctx,
        &astar,
        astarIndex,
        npcIndex,
        moverBox,
        moverCenter,
        moverBoxBuffer,
        destCol,
        targetNpcIndex,
        isPlayerBlocking]()
    {
        defer(astarFree(ctx.astarPool, astarIndex));

        NPCAi& npcAi = ctx.data.npc.ai;
        npcAi.path.status[npcIndex].store(NPCPathStatus::WAITING_FOR_PATH, std::memory_order_relaxed);

        int pathBuffer[ASTAR_MAX_PATH];
        int length = runAStar(
            astar,
            astarIndex,
            ctx,
            npcIndex,
            moverBox,
            moverCenter,
            moverBoxBuffer,
            destCol,
            targetNpcIndex,
            isPlayerBlocking,
            pathBuffer);

        if (length > 0)
        {
            for (int i = 0; i < length; i++)
            {
                SDL_Point p = astarDecode(astar, astarIndex, pathBuffer[i]);
                npcAi.path.point.x[npcIndex][i] = p.x;
                npcAi.path.point.y[npcIndex][i] = p.y;
            }
            npcAi.path.length[npcIndex] = (uint32_t)length;
            npcAi.path.index[npcIndex]  = 0;
            // release: guarantees path data writes above are visible to main thread on acquire load
            npcAi.path.status[npcIndex].store(NPCPathStatus::CALCULATION_FINISHED, std::memory_order_release);
        }
        else
        {
            npcAi.path.status[npcIndex].store(NPCPathStatus::CALCULATION_FAILED, std::memory_order_relaxed);
        }
    });
}
