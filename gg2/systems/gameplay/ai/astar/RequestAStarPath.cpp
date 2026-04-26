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
                      SDL_FPoint start, const SDL_FRect& destCol, int speed)
{
    NPCAi& npcAi = ctx.data.npc.ai;

    npcAi.pathStatus[npcIndex] = NPCPathStatus::STARTED;

    int astarIndex = astarAlloc(ctx.astarPool);
    if (astarIndex == -1)
        return;

    AStarContext& astar = ctx.astarPool.ctx[astarIndex];
    astar.status = AStarStatus::STARTED;

    std::async(std::launch::async, [&ctx, &astar, astarIndex, npcIndex, start, destCol, speed]()
    {
        defer(astarFree(ctx.astarPool, astarIndex));

        NPCAi& npcAi = ctx.data.npc.ai;
        npcAi.pathStatus[npcIndex] = NPCPathStatus::WAITING_FOR_PATH;

        int pathBuffer[ASTAR_MAX_PATH];
        int length = runAStar(astar, ctx, start, destCol, speed, pathBuffer);

        if (length > 0)
        {
            for (int i = 0; i < length; i++)
            {
                int x, y;
                astarDecode(astar, pathBuffer[i], x, y);
                npcAi.path.x[npcIndex][i] = x;
                npcAi.path.y[npcIndex][i] = y;
            }
            npcAi.pathLength[npcIndex] = (uint32_t)length;
            npcAi.pathIndex[npcIndex]  = 0;
            npcAi.pathStatus[npcIndex] = NPCPathStatus::CALCULATION_FINISHED;
        }
        else
        {
            npcAi.pathStatus[npcIndex] = NPCPathStatus::CALCULATION_FAILED;
        }
    });
}
