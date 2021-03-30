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
        auto jobTypeStr = jobTypeToString(jobType);
        auto powerLevelStr = powerLevelToString(powerLevel);

        return jobTypeStr + " " + std::to_string(duration) + " " + powerLevelStr;
    }

    std::string Job::toJson()
    {
        auto jobTypeStr = jobTypeToString(jobType);
        auto powerLevelStr = powerLevelToString(powerLevel);

        return "{\n\t\"jobType\": " + jobTypeStr 
                + ",\n\t\"duration\": " + std::to_string(duration) 
                + ",\n\t\"powerLevel\": " + powerLevelStr + "\n}";
    }
}
