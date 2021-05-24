#include "JobGeneratorService.h"
#include "../domain/JobGenerator.h"
#include <iostream>

namespace service
{
    domain::Job JobGeneratorService::GenerateJob(domain::JobType jobType, int weight, std::string food, domain::IPresetService *presetSerivce)
    {
        
        domain::Preset *preset = presetSerivce->getPresetByFood(food);
        if (preset != NULL)
        {
            return preset->getJob();
        }
        
        return domain::JobGenerator::GenerateJob(jobType, weight, food);
    }
}