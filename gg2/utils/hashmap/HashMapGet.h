#pragma once
#include "HashMap.h"
#include "HashMapFind.h"

template<typename T, int Size>
T hashMapGet(const HashMap<T, Size>& map, int node, int generation, T defaultVal)
{
    int s = hashMapFind(map, node, generation);
    if (s == -1 || map.node[s] != node) return defaultVal;
    return map.value[s];
}
