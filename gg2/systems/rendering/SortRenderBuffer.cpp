#include "SortRenderBuffer.h"
#include <functional>
#include <algorithm>

void SortRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    if (rb.count <= 1) return;

    auto rbSwap = [&](uint32_t a, uint32_t b) {
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
    auto depthKey = [&](uint32_t i) { return rb.dst.y[i] + rb.dst.colOffY[i]; };
    std::function<void(int, int)> rbSort = [&](int lo, int hi) {
        if (lo >= hi) return;
        float pivot = depthKey(lo + (hi - lo) / 2);
        int i = lo, j = hi;
        while (i <= j) {
            while (depthKey(i) < pivot) i++;
            while (depthKey(j) > pivot) j--;
            if (i <= j) { rbSwap(i++, j--); }
        }
        rbSort(lo, j);
        rbSort(i, hi);
    };
    rbSort(0, (int)rb.count - 1);
}
