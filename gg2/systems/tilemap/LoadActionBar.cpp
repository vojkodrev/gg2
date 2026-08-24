#include "LoadActionBar.h"
#include "LoadMagicActionBar.h"
#include "LoadRangedActionBar.h"
#include "../../structs/equipment/WeaponType.h"
#include "../../utils/groups/GroupAlloc.h"

void loadActionBar(Context &ctx, const tmx::Tileset &tileset)
{
    auto &actionBar = ctx.data.actionBar;
    actionBar.groupId = groupAlloc(ctx.data.groups);
    const auto &weapon = ctx.data.player.equipment.weapon;
    if (weapon.type[0] == WeaponType::Ranged)
        loadRangedActionBar(ctx, tileset);
    else
        loadMagicActionBar(ctx, tileset);
}
