#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"
#include "../../structs/core/constants/IndexConstants.h"

template<int N, typename T, int Size>
bool hashMapTryGet(const HashMap<N, Size, T>& map, int index, int node, int generation, T& out)
{
    int s = hashMapFindSlot(map, index, node, generation);
    if (s == INVALID_ID || map.gen[index][s] != generation || map.node[index][s] != node) return false;
    out = map.value[index][s];
    return true;
}
