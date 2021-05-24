#pragma once
#include "Job.h"
#include "IPresetService.h"

namespace domain
{
    class IJobGeneratorService
    {
    public:
        virtual domain::Job GenerateJob(domain::JobType jobType, int weight, std::string food, domain::IPresetService *presetService) = 0;
    };
}