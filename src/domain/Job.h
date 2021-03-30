#pragma once
#include "JobType.h"
#include "PowerLevel.h"
#include <string>

namespace domain
{
    class Job
    {
    public:
        Job();
        Job(JobType jobType, int duration, PowerLevel powerLevel);
        //static Job fromStrParams(std::string jobType, int duration, std::string powerLevel);

        JobType getJobType();
        void setJobType(JobType jobType);

        int getDuration();
        void setDuration(int duration);

        PowerLevel getPowerLevel();
        void setPower(PowerLevel power);

        std::string toString();
        std::string toJson();

    private:
        JobType jobType;
        int duration; // in seconds
        PowerLevel powerLevel;
    };
}