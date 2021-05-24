#pragma once
#include "Job.h"
#include <string>

namespace domain
{
    class JobGenerator
    {
        public:
            static Job GenerateJob(JobType jobType, int weight, std::string food);
    };
}