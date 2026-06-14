#pragma once
#include "ColIdType.h"

inline bool isStatic(ColType type) { return type == ColType::Object; }
inline bool isStatic(uint32_t id) { return isStatic(colIdType(id)); }
