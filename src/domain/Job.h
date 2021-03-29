#pragma once
#include "JobType.h"
#include "PowerLevel.h"

namespace domain
{
    class Job
    {
    public:
        Job();
        Job(JobType jobType, int duration, PowerLevel powerLevel);

        JobType getJobType();
        void setJobType(JobType jobType);

        int getDuration();
        void setDuration(int duration);

        PowerLevel getPowerLevel();
        void setPower(PowerLevel power);

    private:
        JobType jobType;
        int duration; // in seconds
        PowerLevel powerLevel;
    };
}