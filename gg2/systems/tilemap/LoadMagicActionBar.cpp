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

    loadEntityBase(
        actionBar.frostNova.base,
        0,
        tileset,
        frostNovaTileIdx,
        ctx.data.tileMapProps);

    auto &base = actionBar.frostNova.base;
    base.position.x[0] = (SCREEN_W - base.position.w[0]) / 2.0f;
    base.position.y[0] =
        SCREEN_H - ACTION_BAR_BOTTOM_PADDING - base.position.h[0];
    base.position.absolute[0] = true;
    base.depthY[0] = ACTION_BAR_DEPTH_Y;

    createTextEffect(
        ctx,
        actionBar.groupId,
        EntityType::ActionBarIcon,
        1,
        DestroyEffectType::None,
        0.0f,
        "2",
        SDL_FPoint{
            base.position.x[0] + ACTION_BAR_DIGIT_PADDING,
            base.position.y[0] + ACTION_BAR_DIGIT_PADDING
        },
        SDL_FColor{CLEAR_TINT_R, CLEAR_TINT_G, CLEAR_TINT_B, CLEAR_TINT_A});
}
