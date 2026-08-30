#pragma once
#include "../../structs/equipment/Equipment.h"
#include "../../structs/equipment/WeaponType.h"
#include "../../structs/core/constants/IndexConstants.h"
#include "../../structs/core/constants/ZIndexConstants.h"
#include "../../structs/tilemap/TileMapProperties.h"
#include "ParseWeaponType.h"
#include "GetTileIndex.h"
#include "LoadAnchors.h"
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
    equipmentData.ammo.zIndex[parentEntityIdx] = AMMO_Z_INDEX;
    equipmentData.weapon.zIndex[parentEntityIdx] = WEAPON_Z_INDEX;
    std::string weaponAssetType = getTileStringProp(tileset, parentEntityTileIndex, "weapon");
    uint32_t weaponIdx = 0;
    bool hasWeapon = !weaponAssetType.empty() &&
        findTileByType(tileset, weaponAssetType, weaponIdx);
    equipmentData.weapon.type[parentEntityIdx] = WeaponType::Melee;
    equipmentData.weapon.magic.castingEffectId[parentEntityIdx] = INVALID_ID;
    equipmentData.weapon.ranged.showAmmo[parentEntityIdx] = false;
    for (int frameIndex = 0;
        frameIndex < MAX_ANIMATION_FRAMES;
        frameIndex++)
    {
        equipmentData.weapon.magic.spellAnchor
            .exists[parentEntityIdx][frameIndex][0] = false;
        equipmentData.weapon.ranged.ammoAnchor
            .exists[parentEntityIdx][frameIndex][0] = false;
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

        auto &spellAnchor = equipmentData.weapon.magic.spellAnchor;
        auto &ammoAnchor = equipmentData.weapon.ranged.ammoAnchor;
        const int frameCount = weaponBase.animation.frameCount[parentEntityIdx];
        for (int frameIndex = 0; frameIndex < frameCount; frameIndex++)
        {
            const uint32_t frameTileIdx =
                weaponTile && !weaponTile->animation.frames.empty()
                ? getTileIndex(
                    weaponTile->animation.frames[frameIndex].tileID,
                    props)
                : weaponIdx;
            loadAnchors(
                spellAnchor,
                parentEntityIdx,
                frameIndex,
                tileset,
                frameTileIdx,
                "spellAnchor",
                weaponBase.scale.value[parentEntityIdx]);
            loadAnchors(
                ammoAnchor,
                parentEntityIdx,
                frameIndex,
                tileset,
                frameTileIdx,
                "ammoAnchor",
                weaponBase.scale.value[parentEntityIdx]);
        }
    }

    std::string ammoType = getTileStringProp(tileset, parentEntityTileIndex, "ammo");
    uint32_t ammoIdx = 0;
    bool hasAmmo = !ammoType.empty() &&
        findTileByType(tileset, ammoType, ammoIdx);
    if (hasWeapon && equipmentData.weapon.type[parentEntityIdx] == WeaponType::Ranged)
    {
        if (!hasAmmo)
            return;
        loadEntityBase(equipmentData.ammo.base, parentEntityIdx, tileset, ammoIdx, props);
        equipmentData.ammo.exists[parentEntityIdx] = true;
        equipmentData.weapon.ranged.showAmmo[parentEntityIdx] = true;
    }
}
