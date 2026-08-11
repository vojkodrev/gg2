#include "LoadEffects.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByType.h"
#include "../../structs/animation/AnimationType.h"
#include "../../structs/core/constants/FontConstants.h"
#include "../../structs/core/constants/TauntConstants.h"
#include "../../structs/core/constants/TintConstants.h"
#include "../../utils/grid/DecodeGridIndex.h"
#include <SDL3/SDL.h>
#include <cstdint>

void loadEffects(Context &ctx, const tmx::Tileset &tileset)
{
    auto &effectTemplate = ctx.data.effectTemplate;
    auto &props = ctx.data.tileMapProps;
    effectTemplate.fontIndex = 0;
    effectTemplate.selectIndex = FONT_GLYPH_COUNT;
    effectTemplate.bloodSplatterIndex = effectTemplate.selectIndex + 1;
    effectTemplate.tauntIndex = effectTemplate.bloodSplatterIndex + 1;

    const SDL_Point fontGrid = decodeGridIndex(FONT_GRID_ID, (int)props.tilesetW);
    const int fontBaseX = fontGrid.x * (int)props.srcTileW;
    const int fontBaseY = fontGrid.y * (int)props.srcTileH;

    for (int i = 0; i < FONT_GLYPH_COUNT; i++)
    {
        const SDL_Point glyphGrid = decodeGridIndex(i, FONT_GLYPH_GRID_W);

        effectTemplate.base.animation.animationType[i] = AnimationType::None;
        effectTemplate.base.animation.animationState[i] = AnimationState::Idle;
        effectTemplate.base.animation.animationStop[i] = AnimationStop::None;
        effectTemplate.base.animation.frameCount[i] = 1;
        effectTemplate.base.animation.frameIndex[i] = 0;
        effectTemplate.base.animation.cycleDuration[i] = 0;
        effectTemplate.base.animation.animationStartTime[i] = SDL_GetTicks();
        effectTemplate.base.animation.rotationStartAngle[i] = 0.0f;
        effectTemplate.base.animation.rotationStopAngle[i] = 0.0f;
        effectTemplate.base.animation.frame.src.x[i][0] = fontBaseX + glyphGrid.x * FONT_GLYPH_W;
        effectTemplate.base.animation.frame.src.y[i][0] = fontBaseY + glyphGrid.y * FONT_GLYPH_H;
        effectTemplate.base.animation.frame.src.w[i][0] = FONT_GLYPH_W;
        effectTemplate.base.animation.frame.src.h[i][0] = FONT_GLYPH_H;
        effectTemplate.base.animation.frame.frameDuration[i][0] = 0;
        effectTemplate.base.animation.rotate[i] = 0.0f;

        effectTemplate.base.position.initialW[i] = FONT_GLYPH_W;
        effectTemplate.base.position.initialH[i] = FONT_GLYPH_H;
        effectTemplate.base.position.w[i] = FONT_GLYPH_W;
        effectTemplate.base.position.h[i] = FONT_GLYPH_H;
        effectTemplate.base.scale.value[i] = 1.0f;

        effectTemplate.base.tint.r[i] = CLEAR_TINT_R;
        effectTemplate.base.tint.g[i] = CLEAR_TINT_G;
        effectTemplate.base.tint.b[i] = CLEAR_TINT_B;
        effectTemplate.base.tint.a[i] = CLEAR_TINT_A;
        effectTemplate.base.tint.damageTimer[i] = 0.0f;
        effectTemplate.base.tint.isPoisoned[i] = false;
    }

    uint32_t selectTileIdx = 0;
    if (findTileByType(tileset, "select", selectTileIdx))
    {
        loadEntityBase(
            effectTemplate.base,
            (uint32_t)effectTemplate.selectIndex,
            tileset,
            selectTileIdx,
            props);
    }

    uint32_t bloodSplatterTileIdx = 0;
    if (findTileByType(tileset, "bloodSplatter", bloodSplatterTileIdx))
    {
        loadEntityBase(
            effectTemplate.base,
            (uint32_t)effectTemplate.bloodSplatterIndex,
            tileset,
            bloodSplatterTileIdx,
            props);
    }

    uint32_t tauntTileIdx = 0;
    if (findTileByType(tileset, "taunt", tauntTileIdx))
    {
        loadEntityBase(
            effectTemplate.base,
            (uint32_t)effectTemplate.tauntIndex,
            tileset,
            tauntTileIdx,
            props);
        effectTemplate.base.tint.r[effectTemplate.tauntIndex] = TAUNT_TINT_R;
        effectTemplate.base.tint.g[effectTemplate.tauntIndex] = TAUNT_TINT_G;
        effectTemplate.base.tint.b[effectTemplate.tauntIndex] = TAUNT_TINT_B;
        effectTemplate.base.tint.a[effectTemplate.tauntIndex] = TAUNT_TINT_A;
    }
}
