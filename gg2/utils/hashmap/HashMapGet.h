#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<int N, typename T, int Size>
T hashMapGet(const HashMap<N, Size, T>& map, int index, int node, int generation, T defaultVal)
{
    int s = hashMapFindSlot(map, index, node, generation);
    if (s == -1 || map.gen[index][s] != generation || map.node[index][s] != node) return defaultVal;
    return map.value[index][s];
}
