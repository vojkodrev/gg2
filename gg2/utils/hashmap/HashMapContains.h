#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<typename T, int Size>
bool hashMapContains(const HashMap<T, Size>& map, int node, int generation)
{
    int s = hashMapFindSlot(map, node, generation);
    return s != -1 && map.gen[s] == generation && map.node[s] == node;
}
