#pragma once
#include "HashMap.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "HashMapFindSlot.h"

template<int N, int Size>
void hashMapInsert(HashMap<N, Size, void>& map, int index, int node, int generation)
{
    int s = hashMapFindSlot(map, index, node, generation);
    if (s == INVALID_ID) return;
    map.node[index][s] = node;
    map.gen[index][s]  = generation;
}
