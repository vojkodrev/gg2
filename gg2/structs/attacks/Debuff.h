#pragma once
#include "../entity/EntityType.h"
#include "../core/constants/AttackConstants.h"
#include "../core/constants/IndexConstants.h"
#include "../../utils/pool/Pool.h"

template<int N>
struct Debuff
{
    Pool<N, MAX_DEBUFF_SLOTS> pool;
    bool active[N] = {};
    float timer[N][MAX_DEBUFF_SLOTS] = {};
    int entityId[N][MAX_DEBUFF_SLOTS];
    EntityType entityType[N][MAX_DEBUFF_SLOTS] = {};

    Debuff()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < MAX_DEBUFF_SLOTS; j++)
            {
                entityId[i][j] = INVALID_ID;
                entityType[i][j] = EntityType::None;
            }
        }
    }
};
