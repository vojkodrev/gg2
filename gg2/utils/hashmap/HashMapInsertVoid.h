#pragma once
#include "HashMap.h"
#include "HashMapFind.h"

template<int Size>
void hashMapInsert(HashMap<void, Size>& map, int node, int generation)
{
    int s = hashMapFind(map, node, generation);
    if (s == -1) return;
    map.node[s] = node;
    map.gen[s]  = generation;
}
