#pragma once
#include "HashMap.h"
#include "HashMapSlot.h"

template<int N, typename T, int Size>
int hashMapFindSlot(const HashMap<N, Size, T>& map, int index, int node, int generation)
{
    int slot = hashMapSlot<Size>(node);
    for (int i = 0; i < Size; i++)
    {
        int s = (slot + i) & (Size - 1);
        if (map.gen[index][s] != generation || map.node[index][s] == node)
            return s;
    }
    return -1;
}
