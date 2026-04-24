#pragma once

template<typename T, int Size>
struct HashMap
{
    int node[Size];
    int gen[Size];
    T   value[Size];
};

template<int Size>
struct HashMap<void, Size>
{
    int node[Size];
    int gen[Size];
};
