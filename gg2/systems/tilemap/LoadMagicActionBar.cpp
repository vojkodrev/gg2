#include "LoadMagicActionBar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByIcon.h"
#include "../gameplay/ui/text/CreateTextEffect.h"
#include "../../structs/entity/EntityType.h"
#include "../../structs/core/constants/ActionBarConstants.h"
#include "../../structs/core/constants/ZIndexConstants.h"
#include "../../structs/core/constants/ScreenConstants.h"
#include "../../structs/core/constants/TintConstants.h"
#include "../../structs/effect/DestroyEffectType.h"
#include <string>

void loadMagicActionBar(Context &ctx, const tmx::Tileset &tileset)
{
    auto &actionBar = ctx.data.actionBar;
    actionBar.frostNovaIndex = 0;
    actionBar.arcaneExplosionIndex = 1;

    uint32_t tileIndex = 0;
    if (findTileByIcon(tileset, "frostNova", tileIndex))
    {
        loadEntityBase(
            actionBar.icon.base,
            actionBar.frostNovaIndex,
            tileset,
            tileIndex,
            ctx.data.tileMapProps);
        actionBar.icon.active[actionBar.frostNovaIndex] = true;
        actionBar.icon.zIndex[actionBar.frostNovaIndex] =
            ACTION_BAR_ICON_Z_INDEX;
    }
    if (findTileByIcon(tileset, "arcaneExplosion", tileIndex))
    {
        loadEntityBase(
            actionBar.icon.base,
            actionBar.arcaneExplosionIndex,
            tileset,
            tileIndex,
            ctx.data.tileMapProps);
        actionBar.icon.active[actionBar.arcaneExplosionIndex] = true;
        actionBar.icon.zIndex[actionBar.arcaneExplosionIndex] =
            ACTION_BAR_ICON_Z_INDEX;
    }

    auto &base = actionBar.icon.base;
    const int frostNovaIndex = actionBar.frostNovaIndex;
    const int arcaneExplosionIndex = actionBar.arcaneExplosionIndex;
    const float totalW = base.position.w[frostNovaIndex] +
        ACTION_BAR_ICON_GAP + base.position.w[arcaneExplosionIndex];
    const float startX = (SCREEN_W - totalW) / 2.0f;
    const float bottomY = SCREEN_H - ACTION_BAR_BOTTOM_PADDING;

    base.position.x[frostNovaIndex] = startX;
    base.position.y[frostNovaIndex] =
        bottomY - base.position.h[frostNovaIndex];
    base.position.absolute[frostNovaIndex] = true;
    base.depthY[frostNovaIndex] = ACTION_BAR_DEPTH_Y;

    base.position.x[arcaneExplosionIndex] =
        startX + base.position.w[frostNovaIndex] + ACTION_BAR_ICON_GAP;
    base.position.y[arcaneExplosionIndex] =
        bottomY - base.position.h[arcaneExplosionIndex];
    base.position.absolute[arcaneExplosionIndex] = true;
    base.depthY[arcaneExplosionIndex] = ACTION_BAR_DEPTH_Y;

    const SDL_FColor whiteTint = {
        CLEAR_TINT_R,
        CLEAR_TINT_G,
        CLEAR_TINT_B,
        CLEAR_TINT_A
    };
    const int iconIndexes[] = {frostNovaIndex, arcaneExplosionIndex};
    for (int i = 0; i < 2; i++)
    {
        const int iconIndex = iconIndexes[i];
        createTextEffect(
            ctx,
            actionBar.groupId,
            EntityType::ActionBarIcon,
            iconIndex,
            DestroyEffectType::None,
            0.0f,
            std::to_string(i + 1),
            SDL_FPoint{
                base.position.x[iconIndex] + ACTION_BAR_DIGIT_PADDING,
                base.position.y[iconIndex] + ACTION_BAR_DIGIT_PADDING
            },
            whiteTint);
    }
}
