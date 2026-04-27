#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<typename T, int Size>
T hashMapGet(const HashMap<T, Size>& map, int node, int generation, T defaultVal)
{
    int s = hashMapFindSlot(map, node, generation);
    if (s == -1 || map.gen[s] != generation || map.node[s] != node) return defaultVal;
    return map.value[s];
}
