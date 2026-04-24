#pragma once
#include "HashMap.h"
#include "HashMapSlot.h"

template<typename T, int Size>
int hashMapFind(const HashMap<T, Size>& map, int node, int generation)
{
    int slot = hashMapSlot<Size>(node);
    for (int i = 0; i < Size; i++)
    {
        int s = (slot + i) & (Size - 1);
        if (map.gen[s] != generation || map.node[s] == node)
            return s;
    }
    return -1;
}
