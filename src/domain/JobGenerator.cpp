#include "JobGenerator.h"
#include "Job.h"
#include <algorithm>
#include <string>

#define HIGH_MAX_WEIGHT 500
#define MEAT_DIVIDER_HIGH 6
#define MEAT_DIVIDER_MEDIUM 4
#define VEGETABLES_DIVIDER_HIGH 8
#define VEGETABLES_DIVIDER_MEDIUM 6
#define OTHERS_DIVIDER_HIGH 7
#define OTHERS_DIVIDER_MEDIUM 5

#define MEAT_DEFROST_DIVIDER 2
#define VEGETABLES_DEFROST_DIVIDER 4
#define OTHERS_DEFROST_DIVIDER 3

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
            if (food == "meat")
                duration = weight / MEAT_DEFROST_DIVIDER;
            else if (food == "vegetables")
                duration = weight / VEGETABLES_DEFROST_DIVIDER;
            else
                duration = weight / OTHERS_DEFROST_DIVIDER;
        }
        else
        {
            powerLevel = weight < HIGH_MAX_WEIGHT ? HIGH : MEDIUM;  // high power will burn some parts 
                                                                    // before warming other parts for over the max weight
            if(food == "meat")
                duration = weight < HIGH_MAX_WEIGHT ? weight / MEAT_DIVIDER_HIGH : weight / MEAT_DIVIDER_MEDIUM;
            else if (food == "vegetables")
                duration = weight < HIGH_MAX_WEIGHT ? weight / VEGETABLES_DIVIDER_HIGH : weight / VEGETABLES_DIVIDER_MEDIUM;
            else 
                duration = weight < HIGH_MAX_WEIGHT ? weight / OTHERS_DIVIDER_HIGH : weight / OTHERS_DIVIDER_MEDIUM;
        }

        return Job(jobType, duration, powerLevel);
    }
}