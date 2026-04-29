#include "SortRenderBuffer.h"
#include "../../utils/sort/QuickSort.h"
#include <algorithm>

void sortRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    if (rb.count <= 1) return;

    auto rbSwap = [&](int a, int b) {
        std::swap(rb.src.x[a], rb.src.x[b]);
        std::swap(rb.src.y[a], rb.src.y[b]);
        std::swap(rb.src.w[a], rb.src.w[b]);
        std::swap(rb.src.h[a], rb.src.h[b]);
        std::swap(rb.dst.x[a], rb.dst.x[b]);
        std::swap(rb.dst.y[a], rb.dst.y[b]);
        std::swap(rb.dst.w[a], rb.dst.w[b]);
        std::swap(rb.dst.h[a], rb.dst.h[b]);
        std::swap(rb.dst.colOffY[a], rb.dst.colOffY[b]);
    };
    auto depthKey = [&](int i) { return rb.dst.y[i] + rb.dst.colOffY[i]; };

    quickSort<float>(0, (int)rb.count - 1, depthKey, rbSwap);
}
