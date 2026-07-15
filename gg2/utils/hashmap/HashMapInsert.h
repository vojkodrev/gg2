#pragma once
#include "HashMap.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "HashMapFindSlot.h"

template<int N, typename T, int Size>
void hashMapInsert(HashMap<N, Size, T>& map, int index, int node, int generation, T value)
{
    int s = hashMapFindSlot(map, index, node, generation);
    if (s == INVALID_ID) return;
    map.node[index][s]  = node;
    map.gen[index][s]   = generation;
    map.value[index][s] = value;
}
