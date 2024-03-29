#pragma once
#include <string>

namespace domain
{
    enum JobType
    {
        WARM,
        DEFROST
    };

    JobType jobTypeFromString(std::string str);
    std::string jobTypeToString(JobType jobType);
}