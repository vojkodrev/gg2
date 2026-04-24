#include "ClosedSlot.h"

int closedSlot(int node)
{
    return (node * 2654435761u) >> (32 - 16);
}
