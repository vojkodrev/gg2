#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"

void   gscoreSet(AStarGScoreMap& gm, int node, int generation, float g);
float  gscoreGet(const AStarGScoreMap& gm, int node, int generation);
