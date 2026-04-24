#pragma once
#include "HashMap.h"
#include "HashMapFind.h"

template<typename T, int Size>
bool hashMapTryGet(const HashMap<T, Size>& map, int node, int generation, T& out)
{
    int s = hashMapFind(map, node, generation);
    if (s == -1 || map.node[s] != node) return false;
    out = map.value[s];
    return true;
}
