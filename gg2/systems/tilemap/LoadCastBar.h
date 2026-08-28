#pragma once
#include "LoadProgressBar.h"
#include "../../structs/core/Context.h"
#include "../../structs/core/constants/ActionBarConstants.h"
#include "../../structs/core/constants/CastBarConstants.h"
#include "../../structs/core/constants/ScreenConstants.h"
#include <cstdint>
#include <tmxlite/Tileset.hpp>

inline void loadCastBar(
    Context &ctx,
    const tmx::Tileset &tileset,
    uint32_t playerTileIndex,
    const TileMapProperties &props)
{
    auto &castBar = ctx.data.player.castbar;
    loadProgressBar(
        castBar,
        0,
        tileset,
        playerTileIndex,
        props,
        "castbar");

    auto &base = castBar.base;
    base.position.x[0] = (SCREEN_W - base.position.w[0]) / 2.0f;
    base.position.y[0] =
        SCREEN_H -
        ACTION_BAR_BOTTOM_PADDING -
        ACTION_BAR_ICON_H -
        CAST_BAR_ACTION_BAR_SEPARATOR -
        base.position.h[0];
    base.position.absolute[0] = true;
    base.depthY[0] = CAST_BAR_DEPTH_Y;
}
