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
}