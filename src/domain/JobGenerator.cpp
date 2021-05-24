#include "JobGenerator.h"
#include "Job.h"
#include <algorithm>
#include <string>

#define MAX_WEIGHT_FOR_HIGH_POWER 500
#define DIVIDER_HIGH 7
#define DIVIDER_MEDIUM 5
#define DIVIDER_LOW 3

namespace domain
{
    Job JobGenerator::GenerateJob(JobType jobType, int weight, std::string food)
    {
        PowerLevel powerLevel;
        int duration;
        // convert food to lower case
        std::for_each(food.begin(), food.end(), [](char & c) {
            c = ::tolower(c);
        });

        if (jobType == DEFROST)
        {
            powerLevel = LOW;
            duration = weight / DIVIDER_LOW;
        }
        else
        {
            powerLevel = weight < MAX_WEIGHT_FOR_HIGH_POWER ? HIGH : MEDIUM;  // high power will burn some parts before warming others for 
                                                                              // more than MAX_WEIGHT_FOR_HIGH_POWER grams
            duration = weight < MAX_WEIGHT_FOR_HIGH_POWER ? weight / DIVIDER_HIGH : weight / DIVIDER_MEDIUM;
        }

        return Job(jobType, duration, powerLevel);
    }
}