#include "DebugFpsSystem.h"
#include "ClearDebugFpsEffects.h"
#include "FormatDebugFrameTime.h"
#include "FormatDebugTime.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/core/constants/DebugConstants.h"
#include "../../../structs/core/constants/FontConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../utils/groups/GroupAlloc.h"
#include "../../../utils/math/CalcEma.h"
#include "../../gameplay/ui/text/CreateTextEffect.h"
#include <SDL3/SDL.h>
#include <string>

void debugFpsSystem(Context &ctx)
{
    if (!ctx.data.debug.showFps)
    {
        clearDebugFpsEffects(ctx);
        return;
    }

    calcEma(ctx.frame.frameTime, ctx.data.fps.avgFrameTime);

    if (ctx.frame.frameCount % DEBUG_FPS_UPDATE_FRAME_INTERVAL != 0)
        return;

    clearDebugFpsEffects(ctx);

    if (ctx.data.fps.groupId == INVALID_ID)
        ctx.data.fps.groupId = groupAlloc(ctx.data.groups);

    const std::string frameText = formatDebugFrameTime(ctx.data.fps.avgFrameTime);
    const std::string astarText = formatDebugTime(ctx.data.fps.avgAstarTime);
    const int groupId = ctx.data.fps.groupId;
    const SDL_FColor tint = {
        DEBUG_FPS_TINT_R,
        DEBUG_FPS_TINT_G,
        DEBUG_FPS_TINT_B,
        DEBUG_FPS_TINT_A
    };
    createTextEffect(
        ctx,
        groupId,
        EntityType::Window,
        0,
        DestroyEffectType::None,
        0.0f,
        frameText,
        SDL_FPoint{
            DEBUG_FPS_LEFT_PADDING,
            DEBUG_FPS_TOP_PADDING
        },
        tint,
        &ctx.data.fps.characterEffectIds);
    createTextEffect(
        ctx,
        groupId,
        EntityType::Window,
        0,
        DestroyEffectType::None,
        0.0f,
        astarText,
        SDL_FPoint{
            DEBUG_FPS_LEFT_PADDING,
            DEBUG_FPS_TOP_PADDING + FONT_GLYPH_H
        },
        tint,
        &ctx.data.fps.characterEffectIds);
}
