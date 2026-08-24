#include "LoadRangedActionBar.h"
#include "LoadEntityBase.h"
#include "properties/FindTileByIcon.h"
#include "../gameplay/ui/text/CreateTextEffect.h"
#include "../../structs/entity/EntityType.h"
#include "../../structs/core/constants/ActionBarConstants.h"
#include "../../structs/core/constants/ScreenConstants.h"
#include "../../structs/core/constants/TintConstants.h"
#include "../../structs/effect/DestroyEffectType.h"
#include <string>

void loadRangedActionBar(Context &ctx, const tmx::Tileset &tileset)
{
    auto &props = ctx.data.tileMapProps;
    auto &actionBar = ctx.data.actionBar;
    auto &base = actionBar.icon.base;
    actionBar.rangedAutoAttackIndex = 0;
    actionBar.serpentStingIndex = 1;
    actionBar.concussiveShotIndex = 2;
    actionBar.petAutoAttackIndex = 3;
    actionBar.petTauntIndex = 4;

    uint32_t tileIndex = 0;
    if (findTileByIcon(tileset, "rangedAutoAttack", tileIndex))
    {
        loadEntityBase(base, actionBar.rangedAutoAttackIndex, tileset, tileIndex, props);
        actionBar.icon.active[actionBar.rangedAutoAttackIndex] = true;
    }
    if (findTileByIcon(tileset, "serpentSting", tileIndex))
    {
        loadEntityBase(base, actionBar.serpentStingIndex, tileset, tileIndex, props);
        actionBar.icon.active[actionBar.serpentStingIndex] = true;
    }
    if (findTileByIcon(tileset, "concussiveShot", tileIndex))
    {
        loadEntityBase(base, actionBar.concussiveShotIndex, tileset, tileIndex, props);
        actionBar.icon.active[actionBar.concussiveShotIndex] = true;
    }
    if (findTileByIcon(tileset, "petAutoAttack", tileIndex))
    {
        loadEntityBase(base, actionBar.petAutoAttackIndex, tileset, tileIndex, props);
        actionBar.icon.active[actionBar.petAutoAttackIndex] = true;
    }
    if (findTileByIcon(tileset, "taunt", tileIndex))
    {
        loadEntityBase(base, actionBar.petTauntIndex, tileset, tileIndex, props);
        actionBar.icon.active[actionBar.petTauntIndex] = true;
    }

    const int rangedIndex = actionBar.rangedAutoAttackIndex;
    const int serpentIndex = actionBar.serpentStingIndex;
    const int concussiveIndex = actionBar.concussiveShotIndex;
    const int petIndex = actionBar.petAutoAttackIndex;
    const int petTauntIndex = actionBar.petTauntIndex;
    const float rangedW = base.position.w[rangedIndex];
    const float rangedH = base.position.h[rangedIndex];
    const float serpentW = base.position.w[serpentIndex];
    const float serpentH = base.position.h[serpentIndex];
    const float concussiveW = base.position.w[concussiveIndex];
    const float concussiveH = base.position.h[concussiveIndex];
    const float petW = base.position.w[petIndex];
    const float petH = base.position.h[petIndex];
    const float petTauntW = base.position.w[petTauntIndex];
    const float petTauntH = base.position.h[petTauntIndex];
    const float totalW =
        rangedW + serpentW + concussiveW + petW + petTauntW +
        ACTION_BAR_ICON_GAP * 3.0f + ACTION_BAR_PET_SECTION_GAP;
    const float startX = (SCREEN_W - totalW) / 2.0f;
    const float bottomY = SCREEN_H - ACTION_BAR_BOTTOM_PADDING;

    base.position.x[rangedIndex] = startX;
    base.position.y[rangedIndex] = bottomY - rangedH;
    base.position.absolute[rangedIndex] = true;
    base.depthY[rangedIndex] = ACTION_BAR_DEPTH_Y;

    base.position.x[serpentIndex] = startX + rangedW + ACTION_BAR_ICON_GAP;
    base.position.y[serpentIndex] = bottomY - serpentH;
    base.position.absolute[serpentIndex] = true;
    base.depthY[serpentIndex] = ACTION_BAR_DEPTH_Y;

    base.position.x[concussiveIndex] =
        base.position.x[serpentIndex] + serpentW + ACTION_BAR_ICON_GAP;
    base.position.y[concussiveIndex] = bottomY - concussiveH;
    base.position.absolute[concussiveIndex] = true;
    base.depthY[concussiveIndex] = ACTION_BAR_DEPTH_Y;

    base.position.x[petIndex] =
        base.position.x[concussiveIndex] + concussiveW +
        ACTION_BAR_PET_SECTION_GAP;
    base.position.y[petIndex] = bottomY - petH;
    base.position.absolute[petIndex] = true;
    base.depthY[petIndex] = ACTION_BAR_DEPTH_Y;

    base.position.x[petTauntIndex] =
        base.position.x[petIndex] + petW + ACTION_BAR_ICON_GAP;
    base.position.y[petTauntIndex] = bottomY - petTauntH;
    base.position.absolute[petTauntIndex] = true;
    base.depthY[petTauntIndex] = ACTION_BAR_DEPTH_Y;

    const SDL_FColor whiteTint = {
        CLEAR_TINT_R,
        CLEAR_TINT_G,
        CLEAR_TINT_B,
        CLEAR_TINT_A
    };
    const int numberedIconIndexes[] = {
        rangedIndex,
        serpentIndex,
        concussiveIndex,
        petIndex
    };
    for (int i = 0; i < 4; i++)
    {
        const int iconIndex = numberedIconIndexes[i];
        createTextEffect(
            ctx,
            actionBar.groupId,
            EntityType::ActionBarIcon,
            iconIndex,
            DestroyEffectType::None,
            0.0f,
            std::to_string(i + 1),
            SDL_FPoint{
                base.position.x[iconIndex] + ACTION_BAR_DIGIT_PADDING,
                base.position.y[iconIndex] + ACTION_BAR_DIGIT_PADDING
            },
            whiteTint);
    }
}
