#pragma once
#include "../../structs/equipment/WeaponType.h"
#include <string>

inline bool parseWeaponType(const std::string &weaponAssetType, WeaponType &weaponType)
{
    if (weaponAssetType == "bow1")
    {
        weaponType = WeaponType::Ranged;
        return true;
    }

    if (
        weaponAssetType == "polearm1" ||
        weaponAssetType == "staff1" ||
        weaponAssetType == "sword1")
    {
        weaponType = WeaponType::Melee;
        return true;
    }

    return false;
}
