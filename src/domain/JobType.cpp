#include "JobType.h"
#include <algorithm>

namespace domain
{
    JobType jobTypeFromString(std::string str)
    {
        for (auto &c : str)
        {
            c = toupper(c);
        }

        if (!str.compare("WARM"))
        {
            return JobType::WARM;
        }

        return JobType::DEFROST;
    }
}