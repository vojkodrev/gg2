#pragma once
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>

inline std::string formatDebugTime(float value)
{
    const float roundedValue = std::round(value * 100.0f) / 100.0f;
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << roundedValue;
    return stream.str();
}
