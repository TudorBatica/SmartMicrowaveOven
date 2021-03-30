#pragma once
#include <string>

namespace domain
{
    enum PowerLevel
    {
        LOW,
        MEDIUM,
        HIGH
    };

    PowerLevel powerLevelFromString(std::string str);
    std::string powerLevelToString(PowerLevel powerLevel);
}