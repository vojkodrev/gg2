#include "MonsterRangedAttack.h"
#include "GetMonsterRangedRetreatPoint.h"
#include "IsMonsterRangedAttackTargetTooClose.h"
#include "IsMonsterRangedTargetVisible.h"
#include "PrepareMonsterAttack.h"
#include "SelectAttackingMonsterIfPlayerHasNoSelection.h"
#include "SetMonsterFacingTowardTarget.h"
#include "../../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../../structs/core/constants/NpcMonsterConstants.h"
#include "../../../../structs/equipment/WeaponType.h"
#include "../../attacks/TryExecuteConcussiveShot.h"
#include "../../attacks/TryExecuteRangedAutoAttack.h"
#include "../HasReachedRect.h"
#include "../SetNpcAiStatePursueTarget.h"
#include "../ResetNpcFollowPath.h"
#include "../astar/FollowAStarPathTo.h"
#include "../../../../utils/rect/CenteredRect.h"

void monsterRangedAttack(Context &ctx, uint32_t n)
{
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterAttack(ctx, n, targetType, targetId, targetCol))
        return;

    auto &npc = ctx.data.npc;
    if (npc.equipment.weapon.type[n] != WeaponType::Ranged)
        return;

    if (isMonsterRangedAttackTargetTooClose(ctx, n, targetType, targetId))
    {
        auto &ai = npc.ai;
        if (!ai.retreating[n] &&
            ai.rangedRetreatPointCheckTimer[n] <= 0.0f)
        {
            ai.rangedRetreatPointCheckTimer[n] =
                NPC_RANGED_RETREAT_POINT_CHECK_TIME;
            const SDL_FPoint retreatPoint =
                getMonsterRangedRetreatPoint(ctx, n, targetCol);
            ai.retreatPointX[n] = retreatPoint.x;
            ai.retreatPointY[n] = retreatPoint.y;
            ai.retreating[n] = true;
            resetNpcFollowPath(ctx, n);
        }

        const SDL_FRect retreatRect = centeredRect(
            {ai.retreatPointX[n], ai.retreatPointY[n]},
            (float)NPC_MONSTER_PATH_STEP,
            (float)NPC_MONSTER_PATH_STEP);
        followAStarPathTo(n, ctx, retreatRect, INVALID_ID);
        if (hasReachedRect(ctx, n, retreatRect))
        {
            ai.retreating[n] = false;
            ai.rangedAttackTargetTooCloseCheckTimer[n] = 0.0f;
        }

        if (!isMonsterRangedTargetVisible(ctx, n, targetCol))
            return;
    }
    else if (npc.ai.retreating[n])
    {
        npc.ai.retreating[n] = false;
        resetNpcFollowPath(ctx, n);
    }

    if (!isMonsterRangedTargetVisible(
            ctx,
            n,
            targetCol))
    {
        setNpcAiStatePursueTarget(ctx, n);
        return;
    }

    setMonsterFacingTowardTarget(ctx, n, targetCol);

    bool rangedAutoAttackExecuted = false;
    if (npc.ai.rangedAttackStaggerTimer[n] <= 0.0f &&
        npc.autoAttack.attackTimer[n] <= 0.0f)
    {
        rangedAutoAttackExecuted = tryExecuteRangedAutoAttack(
            ctx,
            EntityType::NPC,
            static_cast<int>(n),
            targetType,
            targetId,
            npc.autoAttack,
            npc.equipment.weapon,
            NPC_RANGED_AUTO_ATTACK_DELAY);
        if (rangedAutoAttackExecuted)
            npc.ai.rangedAttackStaggerTimer[n] =
                NPC_RANGED_ATTACK_STAGGER_TIME;
    }

    bool concussiveShotExecuted = false;
    if (npc.ai.rangedAttackStaggerTimer[n] <= 0.0f)
    {
        concussiveShotExecuted = tryExecuteConcussiveShot(
            ctx,
            EntityType::NPC,
            static_cast<int>(n),
            targetType,
            targetId,
            npc.concussiveShotCooldownTimer[n],
            npc.globalCooldownTimer[n],
            npc.statistics.mana,
            npc.equipment.weapon,
            CONCUSSIVE_SHOT_PROJECTILE_OFFSET);
        if (concussiveShotExecuted)
            npc.ai.rangedAttackStaggerTimer[n] =
                NPC_RANGED_ATTACK_STAGGER_TIME;
    }
    if (!rangedAutoAttackExecuted && !concussiveShotExecuted)
        return;

    selectAttackingMonsterIfPlayerHasNoSelection(
        ctx,
        n,
        targetType,
        targetId);
}
