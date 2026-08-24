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

    uint32_t rangedAutoAttackTileIdx = 0;
    if (findTileByIcon(tileset, "rangedAutoAttack", rangedAutoAttackTileIdx))
        loadEntityBase(actionBar.rangedAutoAttack.base, 0, tileset, rangedAutoAttackTileIdx, props);

    uint32_t petAutoAttackTileIdx = 0;
    if (findTileByIcon(tileset, "petAutoAttack", petAutoAttackTileIdx))
        loadEntityBase(actionBar.petAutoAttack.base, 0, tileset, petAutoAttackTileIdx, props);

    uint32_t petTauntTileIdx = 0;
    if (findTileByIcon(tileset, "taunt", petTauntTileIdx))
        loadEntityBase(actionBar.petTaunt.base, 0, tileset, petTauntTileIdx, props);

    uint32_t serpentStingTileIdx = 0;
    if (findTileByIcon(tileset, "serpentSting", serpentStingTileIdx))
        loadEntityBase(actionBar.serpentSting.base, 0, tileset, serpentStingTileIdx, props);

    uint32_t concussiveShotTileIdx = 0;
    if (findTileByIcon(tileset, "concussiveShot", concussiveShotTileIdx))
        loadEntityBase(actionBar.concussiveShot.base, 0, tileset, concussiveShotTileIdx, props);

    const float rangedW = actionBar.rangedAutoAttack.base.position.w[0];
    const float rangedH = actionBar.rangedAutoAttack.base.position.h[0];
    const float serpentW = actionBar.serpentSting.base.position.w[0];
    const float serpentH = actionBar.serpentSting.base.position.h[0];
    const float concussiveW = actionBar.concussiveShot.base.position.w[0];
    const float concussiveH = actionBar.concussiveShot.base.position.h[0];
    const float petW = actionBar.petAutoAttack.base.position.w[0];
    const float petH = actionBar.petAutoAttack.base.position.h[0];
    const float petTauntW = actionBar.petTaunt.base.position.w[0];
    const float petTauntH = actionBar.petTaunt.base.position.h[0];
    const float totalW =
        rangedW + serpentW + concussiveW + petW + petTauntW +
        ACTION_BAR_ICON_GAP * 3.0f + ACTION_BAR_PET_SECTION_GAP;
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

    actionBar.concussiveShot.base.position.x[0] =
        actionBar.serpentSting.base.position.x[0] + serpentW + ACTION_BAR_ICON_GAP;
    actionBar.concussiveShot.base.position.y[0] = bottomY - concussiveH;
    actionBar.concussiveShot.base.position.absolute[0] = true;
    actionBar.concussiveShot.base.depthY[0] = ACTION_BAR_DEPTH_Y;

    actionBar.petAutoAttack.base.position.x[0] =
        actionBar.concussiveShot.base.position.x[0] + concussiveW + ACTION_BAR_PET_SECTION_GAP;
    actionBar.petAutoAttack.base.position.y[0] = bottomY - petH;
    actionBar.petAutoAttack.base.position.absolute[0] = true;
    actionBar.petAutoAttack.base.depthY[0] = ACTION_BAR_DEPTH_Y;

    actionBar.petTaunt.base.position.x[0] =
        actionBar.petAutoAttack.base.position.x[0] + petW + ACTION_BAR_ICON_GAP;
    actionBar.petTaunt.base.position.y[0] = bottomY - petTauntH;
    actionBar.petTaunt.base.position.absolute[0] = true;
    actionBar.petTaunt.base.depthY[0] = ACTION_BAR_DEPTH_Y;

    const SDL_FColor whiteTint = {
        CLEAR_TINT_R,
        CLEAR_TINT_G,
        CLEAR_TINT_B,
        CLEAR_TINT_A
    };
    const ActionBarIcon *numberedIcons[] = {
        &actionBar.rangedAutoAttack,
        &actionBar.serpentSting,
        &actionBar.concussiveShot,
        &actionBar.petAutoAttack
    };
    for (int i = 0; i < 4; i++)
        createTextEffect(
            ctx,
            actionBar.groupId,
            EntityType::ActionBarIcon,
            i,
            DestroyEffectType::None,
            0.0f,
            std::to_string(i + 1),
            SDL_FPoint{
                numberedIcons[i]->base.position.x[0] + ACTION_BAR_DIGIT_PADDING,
                numberedIcons[i]->base.position.y[0] + ACTION_BAR_DIGIT_PADDING
            },
            whiteTint);
}
