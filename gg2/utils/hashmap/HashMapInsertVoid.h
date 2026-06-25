#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<int N, int Size>
void hashMapInsert(HashMap<N, Size, void>& map, int index, int node, int generation)
{
    int s = hashMapFindSlot(map, index, node, generation);
    if (s == -1) return;
    map.node[index][s] = node;
    map.gen[index][s]  = generation;
}
