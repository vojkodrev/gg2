#pragma once
#include "ColId.h"

inline bool isStatic(uint16_t id) { return colIdIsObject(id); }
