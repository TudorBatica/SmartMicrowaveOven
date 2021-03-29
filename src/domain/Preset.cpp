#include "Preset.h"

namespace domain
{
    Preset::Preset() {}

    Preset::Preset(int presetId, std::string food, Job job)
    {
        this->presetId = presetId;
        this->food = food;
        this->job = job;
    }

    void Preset::setJob(Job job)
    {
        this->job = job;
    }

    Job Preset::getJob()
    {
        return job;
    }

    void Preset::setFood(std::string food)
    {
        this->food = food;
    }

    std::string Preset::getFood()
    {
        return food;
    }

    int Preset::getPresetId()
    {
        return presetId;
    }
}
