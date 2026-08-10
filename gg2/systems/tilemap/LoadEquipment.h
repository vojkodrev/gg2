#pragma once
#include "../../structs/equipment/Equipment.h"
#include "../../structs/equipment/WeaponType.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "ParseWeaponType.h"
#include "GetAnchor.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "properties/GetTileFloatProp.h"
#include "properties/GetTileStringProp.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

template<int N>
inline void loadEquipment(
    Equipment<N> &equipmentData, 
    uint32_t parentEntityIdx, 
    const tmx::Tileset &tileset, 
    uint32_t parentEntityTileIndex, 
    const TileMapProperties &props)
{
    equipmentData.ammo.exists[parentEntityIdx] = false;
    equipmentData.weapon.exists[parentEntityIdx] = false;
    std::string weaponAssetType = getTileStringProp(tileset, parentEntityTileIndex, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponAssetType.empty() && findTileByType(tileset, weaponAssetType.c_str(), weaponIdx);
    equipmentData.weapon.type[parentEntityIdx] = WeaponType::Melee;
    equipmentData.weapon.ranged.showAmmo[parentEntityIdx] = false;
    for (int f = 0; f < MAX_ANIMATION_FRAMES; f++)
    {
        equipmentData.weapon.ranged.ammoAnchor.exists[parentEntityIdx][f] = false;
    }
    if (hasWeapon && parseWeaponType(weaponAssetType, equipmentData.weapon.type[parentEntityIdx]))
    {
        loadEntityBase(equipmentData.weapon.base, parentEntityIdx, tileset, weaponIdx, props);
        equipmentData.weapon.exists[parentEntityIdx] = true;

        auto &weaponBase = equipmentData.weapon.base;
        weaponBase.scale.value[parentEntityIdx] = getTileFloatProp(
            tileset,
            parentEntityTileIndex,
            "weaponScale",
            weaponBase.scale.value[parentEntityIdx]);
        weaponBase.position.w[parentEntityIdx] =
            weaponBase.position.initialW[parentEntityIdx] * weaponBase.scale.value[parentEntityIdx];
        weaponBase.position.h[parentEntityIdx] =
            weaponBase.position.initialH[parentEntityIdx] * weaponBase.scale.value[parentEntityIdx];

        const tmx::Tileset::Tile *weaponTile = nullptr;
        for (const auto &tile : tileset.getTiles())
            if (tile.ID == weaponIdx) { weaponTile = &tile; break; }

        auto &ammoAnchor = equipmentData.weapon.ranged.ammoAnchor;
        const int frameCount = weaponBase.animation.frameCount[parentEntityIdx];
        for (int f = 0; f < frameCount; f++)
        {
            const uint32_t frameTileIdx =
                weaponTile && !weaponTile->animation.frames.empty()
                ? weaponTile->animation.frames[f].tileID - props.firstGid
                : weaponIdx;
            SDL_FRect frameAmmoAnchor;
            ammoAnchor.exists[parentEntityIdx][f] =
                getAnchor(tileset, frameTileIdx, "ammoAnchor", frameAmmoAnchor);
            ammoAnchor.initialOffX[parentEntityIdx][f] = frameAmmoAnchor.x;
            ammoAnchor.initialOffY[parentEntityIdx][f] = frameAmmoAnchor.y;
            ammoAnchor.initialW[parentEntityIdx][f] = frameAmmoAnchor.w;
            ammoAnchor.initialH[parentEntityIdx][f] = frameAmmoAnchor.h;
            ammoAnchor.offX[parentEntityIdx][f] = frameAmmoAnchor.x;
            ammoAnchor.offY[parentEntityIdx][f] = frameAmmoAnchor.y;
            ammoAnchor.w[parentEntityIdx][f] =
                frameAmmoAnchor.w * weaponBase.scale.value[parentEntityIdx];
            ammoAnchor.h[parentEntityIdx][f] =
                frameAmmoAnchor.h * weaponBase.scale.value[parentEntityIdx];
        }
    }

    std::string ammoType = getTileStringProp(tileset, parentEntityTileIndex, "ammo");
    uint32_t ammoIdx = 0;
    bool hasAmmo = !ammoType.empty() && findTileByType(tileset, ammoType.c_str(), ammoIdx);
    if (hasWeapon && equipmentData.weapon.type[parentEntityIdx] == WeaponType::Ranged)
    {
        if (!hasAmmo)
            return;
        loadEntityBase(equipmentData.ammo.base, parentEntityIdx, tileset, ammoIdx, props);
        equipmentData.ammo.exists[parentEntityIdx] = true;
        equipmentData.weapon.ranged.showAmmo[parentEntityIdx] = true;
    }
}
