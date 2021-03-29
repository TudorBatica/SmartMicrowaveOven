#include "Preset.h"

namespace domain
{
    int Preset::nextId = 0;

    Preset::Preset() {}

    Preset::Preset(std::string food, Job job)
    {
        this->presetId = nextId;
        this->food = food;
        this->job = job;
        nextId++;
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

    std::string Preset::toString()
    {
        return std::to_string(presetId) + " " + food + " " + job.toString();
    }
}
