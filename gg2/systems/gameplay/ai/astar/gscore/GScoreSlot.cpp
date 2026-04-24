#include "GScoreSlot.h"

int gscoreSlot(int node)
{
    return (node * 2654435761u) >> (32 - 16);
}
