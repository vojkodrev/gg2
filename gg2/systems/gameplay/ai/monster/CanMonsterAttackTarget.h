#pragma once
#include "../../../../structs/core/EntityType.h"

inline bool canMonsterAttackTarget(EntityType type)
{
    return type == EntityType::Player || type == EntityType::NPC;
}
