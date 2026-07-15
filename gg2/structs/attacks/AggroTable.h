#pragma once
#include <cstdint>
#include "../core/constants/AttackConstants.h"
#include "../core/constants/IndexConstants.h"
#include "../core/EntityType.h"
#include "../../utils/pool/Pool.h"

template<int N>
struct AggroTable
{
    Pool<N, MAX_AGGRO_SLOTS> pool;
    EntityType entityType[N][MAX_AGGRO_SLOTS] = {};
    int entityId[N][MAX_AGGRO_SLOTS];
    float value[N][MAX_AGGRO_SLOTS] = {};
    float maxValue[N] = {};
    EntityType maxEntityType[N] = {};
    int maxEntityId[N];

    AggroTable()
    {
        for (int i = 0; i < N; i++)
        {
            maxEntityType[i] = EntityType::None;
            maxEntityId[i] = INVALID_ID;
            for (int j = 0; j < MAX_AGGRO_SLOTS; j++)
                entityType[i][j] = EntityType::None;
            for (int j = 0; j < MAX_AGGRO_SLOTS; j++)
                entityId[i][j] = INVALID_ID;
        }
    }
};
