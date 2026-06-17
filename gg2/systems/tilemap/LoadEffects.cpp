#include "LoadEffects.h"
#include "../../structs/effect/EffectTemplateType.h"
#include "LoadEntityBase.h"
#include "properties/GetTileStringProp.h"

void loadEffects(Context &ctx, const tmx::Tileset &tileset)
{
    auto &effectTemplate = ctx.data.effectTemplate;
    uint32_t n = 0;

    for (uint32_t i = 0; i < MAX_EFFECTS; i++)
        effectTemplate.type[i] = EffectTemplateType::None;

    for (const auto &tile : tileset.getTiles())
    {
        if (n >= MAX_EFFECTS)
            break;
        if (getTileStringProp(tileset, tile.ID, "type") != "effect")
            continue;

        EffectTemplateType type = EffectTemplateType::None;
        if (getTileStringProp(tileset, tile.ID, "effect") == "healthbar")
            type = EffectTemplateType::Healthbar;
        if (type == EffectTemplateType::None)
            continue;

        effectTemplate.type[n] = type;
        loadEntityBase(
            effectTemplate.base,
            n,
            tileset,
            tile.ID,
            ctx.data.tileMapProps);
        n++;
    }
}
