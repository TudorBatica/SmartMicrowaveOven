#pragma once

#include <string>
#include "Job.h"

namespace domain
{
    class Preset
    {
    public:
        Preset();
        Preset(std::string food, Job job);

        void setJob(Job job);
        Job getJob();

        void setFood(std::string food);
        std::string getFood();

        int getPresetId();

        std::string toString();

    private:
        static int nextId;
        int presetId;
        std::string food;
        Job job;
    };

}