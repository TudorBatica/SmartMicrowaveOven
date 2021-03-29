#include "Job.h"

namespace domain
{
    Job::Job() {}

    Job::Job(JobType jobType, int duration, PowerLevel powerLevel)
    {
        this->jobType = jobType;
        this->duration = duration;
        this->powerLevel = powerLevel;
    }

    JobType Job::getJobType()
    {
        return jobType;
    }

    void Job::setJobType(JobType jobType)
    {
        this->jobType = jobType;
    }

    int Job::getDuration()
    {
        return duration;
    }

    void Job::setDuration(int duration)
    {
        this->duration = duration;
    }

    PowerLevel Job::getPowerLevel()
    {
        return powerLevel;
    }

    void Job::setPower(PowerLevel powerLevel)
    {
        this->powerLevel = powerLevel;
    }

    std::string Job::toString()
    {
        std::string jobTypeStr;
        switch (jobType)
        {
        case WARM:
            jobTypeStr = "Warm";
            break;

        default:
            jobTypeStr = "Defrost";
            break;
        }

        std::string powerLevelStr;
        switch (powerLevel)
        {
        case LOW:
            powerLevelStr = "Low";
            break;

        case MEDIUM:
            powerLevelStr = "Medium";
            break;

        default:
            jobTypeStr = "High";
            break;
        }

        return jobTypeStr + " " + std::to_string(duration) + " " + powerLevelStr;
    }
}
