#pragma once
#include "../domain/IPresetService.h"
#include "../domain/JobGenerator.h"
#include "../domain/IJobGeneratorService.h"


namespace service
{
    class JobGeneratorService : public domain::IJobGeneratorService
    {
        public:
            domain::Job GenerateJob(domain::JobType jobType, int weight, std::string food, domain::IPresetService *presetSerivce);
    };
}