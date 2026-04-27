#pragma once
#include "HashMap.h"
#include "HashMapFindSlot.h"

template<typename T, int Size>
void hashMapInsert(HashMap<T, Size>& map, int node, int generation, T value)
{
    int s = hashMapFindSlot(map, node, generation);
    if (s == -1) return;
    map.node[s]  = node;
    map.gen[s]   = generation;
    map.value[s] = value;
}
