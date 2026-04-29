#pragma once

template<typename TKey, typename FKey, typename FSwap>
void quickSort(int lo, int hi, FKey key, FSwap swap)
{
    if (lo >= hi) return;
    TKey pivot = key(lo + (hi - lo) / 2);
    int i = lo, j = hi;
    while (i <= j)
    {
        while (key(i) < pivot) i++;
        while (key(j) > pivot) j--;
        if (i <= j) { swap(i++, j--); }
    }
    quickSort<TKey>(lo, j, key, swap);
    quickSort<TKey>(i, hi, key, swap);
}
