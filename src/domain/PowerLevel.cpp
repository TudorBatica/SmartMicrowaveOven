#include "PowerLevel.h"

namespace domain
{
    PowerLevel powerLevelFromString(std::string str)
    {
        for (auto &c : str)
        {
            c = toupper(c);
        }

        if (!str.compare("LOW"))
        {
            return PowerLevel::LOW;
        }

        if (!str.compare("MEDIUM"))
        {
            return PowerLevel::MEDIUM;
        }

        return PowerLevel::HIGH;
    }

    std::string powerLevelToString(PowerLevel powerLevel)
    {
        switch (powerLevel)
        {
        case LOW:
            return "Low";
        case MEDIUM:
            return "Medium";
        default:
            return "High";
        }
    }
}