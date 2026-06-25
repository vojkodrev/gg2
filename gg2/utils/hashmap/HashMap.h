#pragma once

template<int N, int Size, typename T>
struct HashMap
{
    int node[N][Size];
    int gen[N][Size];
    T   value[N][Size];
};

template<int N, int Size>
struct HashMap<N, Size, void>
{
    int node[N][Size];
    int gen[N][Size];
};
