#pragma once

template<int Size>
int hashMapSlot(int node)
{
    static_assert((Size & (Size - 1)) == 0, "HashMap Size must be a power of two");
    return (node * 2654435761u) & (Size - 1);
}
