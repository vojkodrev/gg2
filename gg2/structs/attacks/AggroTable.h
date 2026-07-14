#pragma once
#include <cstdint>
#include "../core/constants/AttackConstants.h"
#include "../core/constants/IndexConstants.h"
#include "../../utils/pool/Pool.h"

template<int N>
struct AggroTable
{
    Pool<N, MAX_AGGRO_SLOTS> pool;
    int entityId[N][MAX_AGGRO_SLOTS];
    float value[N][MAX_AGGRO_SLOTS] = {};
    float maxValue[N] = {};
    int maxEntityId[N];

    AggroTable()
    {
        for (int i = 0; i < N; i++)
        {
            maxEntityId[i] = INVALID_ID;
            for (int j = 0; j < MAX_AGGRO_SLOTS; j++)
                entityId[i][j] = INVALID_ID;
        }
    }
};
