#pragma once
#include <cstdint>
#include "../core/constants/AttackConstants.h"
#include "../core/constants/IndexConstants.h"

template<int N>
struct AggroTable
{
    int entityId[N][MAX_AGGRO_SLOTS];
    float value[N][MAX_AGGRO_SLOTS] = {};
    uint32_t count[N] = {};

    AggroTable()
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < MAX_AGGRO_SLOTS; j++)
                entityId[i][j] = INVALID_ID;
    }
};
