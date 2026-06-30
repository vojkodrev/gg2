#include "DebugFpsSystem.h"
#include "ClearDebugFpsEffects.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/DebugConstants.h"
#include "../../../structs/core/constants/FontConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../utils/groups/GroupAlloc.h"
#include "../../gameplay/ui/text/SpawnTextEffect.h"
#include <SDL3/SDL.h>
#include <string>

void debugFpsSystem(Context &ctx)
{
    if (!ctx.data.debug.showFps)
    {
        clearDebugFpsEffects(ctx);
        return;
    }

    if (ctx.frame.frameCount % DEBUG_FPS_UPDATE_FRAME_INTERVAL != 0)
        return;

    clearDebugFpsEffects(ctx);

    if (ctx.data.fps.groupId == -1)
        ctx.data.fps.groupId = groupAlloc(ctx.data.groups);

    const std::string frameText = std::to_string(ctx.frame.frameTime);
    const std::string astarText = std::to_string(ctx.data.fps.astarTime);
    const int groupId = ctx.data.fps.groupId;
    const SDL_FColor tint = {
        DEBUG_FPS_TINT_R,
        DEBUG_FPS_TINT_G,
        DEBUG_FPS_TINT_B,
        DEBUG_FPS_TINT_A
    };
    spawnTextEffect(
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
    spawnTextEffect(
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
