#pragma once
#include "Context.h"
#include "EntityType.h"
#include "IndexConstants.h"
#include "../../npc/select/SetSelectedNpc.h"
#include <cstdint>

inline void selectAttackingMonsterIfPlayerHasNoSelection(
    Context &ctx,
    uint32_t n,
    EntityType targetType,
    int targetId)
{
    if (targetType == EntityType::Player &&
        targetId == 0 &&
        ctx.data.player.selectedNpc == INVALID_ID)
        setSelectedNpc(ctx, static_cast<int>(n));
}
