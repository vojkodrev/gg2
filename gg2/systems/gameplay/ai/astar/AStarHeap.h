#pragma once
#include "../../../../structs/gameplay/ai/AStarContext.h"

void heapPush(AStarHeap& h, int node, float fscore);
int  heapPop(AStarHeap& h);
bool heapEmpty(const AStarHeap& h);
