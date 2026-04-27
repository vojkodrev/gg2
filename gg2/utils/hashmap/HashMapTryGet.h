#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<typename T, int Size>
bool hashMapTryGet(const HashMap<T, Size>& map, int node, int generation, T& out)
{
    int s = hashMapFindSlot(map, node, generation);
    if (s == -1 || map.gen[s] != generation || map.node[s] != node) return false;
    out = map.value[s];
    return true;
}
