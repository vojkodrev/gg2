#include "LoadMagicActionBar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByIcon.h"
#include "../gameplay/ui/text/CreateTextEffect.h"
#include "../../structs/entity/EntityType.h"
#include "../../structs/core/constants/ActionBarConstants.h"
#include "../../structs/core/constants/ScreenConstants.h"
#include "../../structs/core/constants/TintConstants.h"
#include "../../structs/effect/DestroyEffectType.h"

void loadMagicActionBar(Context &ctx, const tmx::Tileset &tileset)
{
    auto &actionBar = ctx.data.actionBar;
    uint32_t frostNovaTileIdx = 0;
    if (!findTileByIcon(tileset, "frostNova", frostNovaTileIdx))
        return;
    actionBar.frostNovaIndex = 0;

    loadEntityBase(
        actionBar.icon.base,
        actionBar.frostNovaIndex,
        tileset,
        frostNovaTileIdx,
        ctx.data.tileMapProps);
    actionBar.icon.active[actionBar.frostNovaIndex] = true;

    auto &base = actionBar.icon.base;
    const int iconIndex = actionBar.frostNovaIndex;
    base.position.x[iconIndex] =
        (SCREEN_W - base.position.w[iconIndex]) / 2.0f;
    base.position.y[iconIndex] =
        SCREEN_H - ACTION_BAR_BOTTOM_PADDING - base.position.h[iconIndex];
    base.position.absolute[iconIndex] = true;
    base.depthY[iconIndex] = ACTION_BAR_DEPTH_Y;

    const SDL_FColor whiteTint = {
        CLEAR_TINT_R,
        CLEAR_TINT_G,
        CLEAR_TINT_B,
        CLEAR_TINT_A
    };
    createTextEffect(
        ctx,
        actionBar.groupId,
        EntityType::ActionBarIcon,
        iconIndex,
        DestroyEffectType::None,
        0.0f,
        "1",
        SDL_FPoint{
            base.position.x[iconIndex] + ACTION_BAR_DIGIT_PADDING,
            base.position.y[iconIndex] + ACTION_BAR_DIGIT_PADDING
        },
        whiteTint);
}
