#include "LoadEffects.h"
#include "../../structs/core/AnimationType.h"
#include "../../structs/core/constants/FontConstants.h"
#include "../../structs/core/constants/TintConstants.h"

void loadEffects(Context &ctx, const tmx::Tileset &tileset)
{
    auto &effectTemplate = ctx.data.effectTemplate;
    auto &props = ctx.data.tileMapProps;
    effectTemplate.fontOffset = 0;

    const int fontBaseX = (FONT_GRID_ID % (int)props.tilesetW) * (int)props.srcTileW;
    const int fontBaseY = (FONT_GRID_ID / (int)props.tilesetW) * (int)props.srcTileH;

    for (int i = 0; i < FONT_GLYPH_COUNT; i++)
    {
        const int glyphCol = i % FONT_GLYPH_GRID_W;
        const int glyphRow = i / FONT_GLYPH_GRID_W;

        effectTemplate.base.animation.animationType[i] = AnimationType::None;
        effectTemplate.base.animation.frameCount[i] = 1;
        effectTemplate.base.animation.frameIndex[i] = 0;
        effectTemplate.base.animation.animationStartTime[i] = 0;
        effectTemplate.base.animation.animationStopTime[i] = 0;
        effectTemplate.base.animation.frame.src.x[i][0] = fontBaseX + glyphCol * FONT_GLYPH_W;
        effectTemplate.base.animation.frame.src.y[i][0] = fontBaseY + glyphRow * FONT_GLYPH_H;
        effectTemplate.base.animation.frame.src.w[i][0] = FONT_GLYPH_W;
        effectTemplate.base.animation.frame.src.h[i][0] = FONT_GLYPH_H;
        effectTemplate.base.animation.frame.frameDuration[i][0] = 0;

        effectTemplate.base.position.initialW[i] = FONT_GLYPH_W;
        effectTemplate.base.position.initialH[i] = FONT_GLYPH_H;
        effectTemplate.base.position.w[i] = FONT_GLYPH_W;
        effectTemplate.base.position.h[i] = FONT_GLYPH_H;
        effectTemplate.base.scale[i] = 1.0f;

        effectTemplate.base.tint.r[i] = CLEAR_TINT_R;
        effectTemplate.base.tint.g[i] = CLEAR_TINT_G;
        effectTemplate.base.tint.b[i] = CLEAR_TINT_B;
        effectTemplate.base.tint.a[i] = CLEAR_TINT_A;
        effectTemplate.base.tint.clearTimer[i] = 0.0f;
    }

    for (const auto &tile : tileset.getTiles())
    {
    }
}
