#pragma once
#include "ActionBarIcon.h"
#include "../core/constants/ActionBarConstants.h"
#include "../core/constants/IndexConstants.h"

struct ActionBar
{
    int groupId = INVALID_ID;
    int rangedAutoAttackIndex = INVALID_ID;
    int petAutoAttackIndex = INVALID_ID;
    int petTauntIndex = INVALID_ID;
    int serpentStingIndex = INVALID_ID;
    int concussiveShotIndex = INVALID_ID;
    int frostNovaIndex = INVALID_ID;
    ActionBarIcon<MAX_ACTION_BAR_ICONS> icon;
};
