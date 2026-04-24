#pragma once
#include "HashMap.h"
#include "HashMapFind.h"

template<typename T, int Size>
bool hashMapContains(const HashMap<T, Size>& map, int node, int generation)
{
    int s = hashMapFind(map, node, generation);
    return s != -1 && map.node[s] == node;
}
