#pragma once
#include "ActionBarIcon.h"
#include "../core/constants/IndexConstants.h"

struct ActionBar
{
    int groupId = INVALID_ID;
    ActionBarIcon rangedAutoAttack;
    ActionBarIcon petAutoAttack;
    ActionBarIcon petTaunt;
    ActionBarIcon serpentSting;
    ActionBarIcon concussiveShot;
};
