#include "SortAggroTable.h"
#include "../../../../utils/sort/QuickSort.h"
#include <algorithm>
#include <utility>

void sortAggroTable(Context &ctx, uint32_t n)
{
    auto &aggroTable = ctx.data.npc.aggroTable;
    const int hi = std::max(0, (int)aggroTable.count[n] - 1);

    auto aggroLess = [&](int a, int b)
    {
        return aggroTable.value[n][a] > aggroTable.value[n][b];
    };
    auto aggroSwap = [&](int a, int b)
    {
        std::swap(aggroTable.entityId[n][a], aggroTable.entityId[n][b]);
        std::swap(aggroTable.value[n][a], aggroTable.value[n][b]);
    };

    quickSort(0, hi, aggroLess, aggroSwap);
}
