#pragma once
#include "../../structs/equipment/WeaponType.h"
#include <string>

inline bool parseWeaponType(const std::string &weaponAssetType, WeaponType &weaponType)
{
    if (weaponAssetType.rfind("bow", 0) == 0)
    {
        weaponType = WeaponType::Ranged;
        return true;
    }

    if (
        weaponAssetType.rfind("polearm", 0) == 0 ||
        weaponAssetType.rfind("staff", 0) == 0 ||
        weaponAssetType.rfind("sword", 0) == 0)
    {
        weaponType = WeaponType::Melee;
        return true;
    }

    return false;
}
