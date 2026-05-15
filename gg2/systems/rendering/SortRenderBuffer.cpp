#include "SortRenderBuffer.h"
#include "RenderBufferOps.h"
#include "../../utils/sort/QuickSort.h"
#include <algorithm>

static bool lessDepth(const RenderBuffer &rb, int a, int b)
{
    if (rb.dst.sortY[a] != rb.dst.sortY[b])
        return rb.dst.sortY[a] < rb.dst.sortY[b];
    if (rb.group.id[a] != rb.group.id[b])
        return rb.group.id[a] < rb.group.id[b];
    return rb.group.zIndex[a] < rb.group.zIndex[b];
}

void sortRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    if (rb.count <= 1) return;

    auto rbSwap = [&](int a, int b) { swapRenderEntry(rb, a, b); };
    auto rbLess = [&](int a, int b) { return lessDepth(rb, a, b); };
    quickSort(0, (int)rb.count - 1, rbLess, rbSwap);
}
