#include "DebugFpsSystem.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/DebugConstants.h"
#include "../../../structs/core/constants/FontConstants.h"
#include "../../../structs/core/constants/TintConstants.h"
#include "../../../utils/queue/QueueDequeue.h"
#include "../../../utils/queue/QueueEmpty.h"
#include "../../../utils/groups/GroupAlloc.h"
#include "../../gameplay/ui/text/SpawnTextEffect.h"
#include "../../gameplay/effects/EffectFree.h"
#include <SDL3/SDL.h>
#include <algorithm>
#include <string>

namespace
{
void clearDebugFpsEffects(Context &ctx)
{
    auto &queue = ctx.data.fps.digitEffectIds;
    while (!queueEmpty(queue))
    {
        const int effectIndex = queueDequeue(queue);
        effectFree(ctx.data.effect, ctx.data.groups, effectIndex);
    }
}
}

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

    const std::string text = std::to_string(ctx.frame.frameTime);
    const int groupId = ctx.data.fps.groupId;
    const float totalW =
        text.size() * FONT_GLYPH_W +
        std::max<int>(0, static_cast<int>(text.size()) - 1) * DAMAGE_NUMBER_DIGIT_SEPARATOR;
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
        text,
        SDL_FPoint{
            DEBUG_FPS_LEFT_PADDING + totalW * 0.5f,
            DEBUG_FPS_TOP_PADDING
        },
        tint,
        &ctx.data.fps.digitEffectIds);
}
