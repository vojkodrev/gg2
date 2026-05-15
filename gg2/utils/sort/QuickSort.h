#pragma once

template<typename FLess, typename FSwap>
void quickSort(int lo, int hi, FLess less, FSwap swap)
{
    if (lo >= hi) return;
    int pivotIndex = lo + (hi - lo) / 2;
    int i = lo, j = hi;
    while (i <= j)
    {
        while (less(i, pivotIndex)) i++;
        while (less(pivotIndex, j)) j--;
        if (i <= j) { swap(i++, j--); }
    }
    quickSort(lo, j, less, swap);
    quickSort(i, hi, less, swap);
}
