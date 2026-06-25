#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<int N, typename T, int Size>
bool hashMapContains(const HashMap<N, Size, T>& map, int index, int node, int generation)
{
    int s = hashMapFindSlot(map, index, node, generation);
    return s != -1 && map.gen[index][s] == generation && map.node[index][s] == node;
}
