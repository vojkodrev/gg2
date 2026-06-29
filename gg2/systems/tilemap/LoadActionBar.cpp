#include "LoadActionBar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByIcon.h"
#include "../../structs/core/constants/ActionBarConstants.h"
#include "../../structs/core/constants/ScreenConstants.h"

void loadActionBar(Context &ctx, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &actionBar = ctx.data.actionBar;

    uint32_t serpentStingTileIdx = 0;
    if (findTileByIcon(tileset, "serpentSting", serpentStingTileIdx))
    {
        loadEntityBase(actionBar.serpentSting.base, 0, tileset, serpentStingTileIdx, props);
    }

    uint32_t rangedAutoAttackTileIdx = 0;
    if (findTileByIcon(tileset, "rangedAutoAttack", rangedAutoAttackTileIdx))
    {
        loadEntityBase(actionBar.rangedAutoAttack.base, 0, tileset, rangedAutoAttackTileIdx, props);
    }

    const float serpentW = actionBar.serpentSting.base.position.w[0];
    const float serpentH = actionBar.serpentSting.base.position.h[0];
    const float rangedW = actionBar.rangedAutoAttack.base.position.w[0];
    const float rangedH = actionBar.rangedAutoAttack.base.position.h[0];
    const float totalW = rangedW + ACTION_BAR_ICON_GAP + serpentW;
    const float startX = (SCREEN_W - totalW) / 2.0f;
    const float bottomY = SCREEN_H - ACTION_BAR_BOTTOM_PADDING;

    actionBar.rangedAutoAttack.base.position.x[0] = startX;
    actionBar.rangedAutoAttack.base.position.y[0] = bottomY - rangedH;
    actionBar.rangedAutoAttack.base.position.absolute[0] = true;
    actionBar.rangedAutoAttack.base.depthY[0] = ACTION_BAR_DEPTH_Y;

    actionBar.serpentSting.base.position.x[0] = startX + rangedW + ACTION_BAR_ICON_GAP;
    actionBar.serpentSting.base.position.y[0] = bottomY - serpentH;
    actionBar.serpentSting.base.position.absolute[0] = true;
    actionBar.serpentSting.base.depthY[0] = ACTION_BAR_DEPTH_Y;
}
