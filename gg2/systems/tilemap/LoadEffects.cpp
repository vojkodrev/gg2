#include "LoadEffects.h"
void loadEffects(Context &ctx, const tmx::Tileset &tileset)
{
    auto &effectTemplate = ctx.data.effectTemplate;

    for (uint32_t i = 0; i < MAX_EFFECTS; i++)
        effectTemplate.type[i] = EffectTemplateType::None;

    for (const auto &tile : tileset.getTiles())
    {
    }
}
