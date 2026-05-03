#include "SortRenderBuffer.h"
#include "RenderBufferOps.h"
#include "../../utils/sort/QuickSort.h"
#include <algorithm>

void sortRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    if (rb.count <= 1) return;

    auto rbSwap = [&](int a, int b) { swapRenderEntry(rb, a, b); };
    auto depthKey = [&](int i) { return rb.dst.y[i] + rb.dst.colOffY[i]; };

    quickSort<float>(0, (int)rb.count - 1, depthKey, rbSwap);
}
