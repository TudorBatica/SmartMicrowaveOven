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

    std::string jobTypeToString(JobType jobType)
    {
        switch (jobType)
        {
        case WARM:
            return "Warm";
        default:
            return "Defrost";
        }
    }
}