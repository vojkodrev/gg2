#pragma once
#include "Context.h"
#include "DebugRenderWeapon.h"
#include "../../../structs/equipment/Equipment.h"

template<int N>
inline void debugRenderEquipment(const Context &ctx, const Equipment<N> &equipment, uint32_t i)
{
    debugRenderWeapon(ctx, equipment.weapon, i);
}
