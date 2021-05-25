#include "PresetRepository.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../domain/Job.h"
#include "../domain/JobType.h"
#include "../domain/PowerLevel.h"


namespace infrastructure
{
    domain::Preset *PresetRepository::findByFood(std::string food)
    {
        if (std::find_if(entities.begin(), entities.end(), [food](domain::Preset &p) { return !p.getFood().compare(food); }) != entities.end())
            return &*std::find_if(entities.begin(), entities.end(), [food](domain::Preset &p) { return !p.getFood().compare(food); });
        else
            return NULL;
    }

    domain::Preset PresetRepository::findById(int presetId)
    {
        return *std::find_if(entities.begin(), entities.end(), [presetId](domain::Preset &p) { return p.getPresetId() == presetId; });
    }

    std::vector<domain::Preset> PresetRepository::findAll()
    {
        return entities;
    }

    void PresetRepository::add(domain::Preset preset)
    {
        entities.push_back(preset);
        std::ofstream presetsCsv;
        presetsCsv.open("presets.csv", std::ios_base::app); // append instead of overwrite

        presetsCsv << preset.getFood() 
                   << "," << domain::jobTypeToString(preset.getJob().getJobType())
                   << "," << preset.getJob().getDuration()
                   << "," << powerLevelToString(preset.getJob().getPowerLevel())
                   << "\n";

        presetsCsv.close();
    }

    PresetRepository::PresetRepository()
    {
        std::ifstream presetsFile("presets.csv");
        std::string line;
        while(presetsFile >> line)
        {
            if(line == "")
                continue;

            std::vector<std::string> tokens;

            std::stringstream check1(line);

            std::string intermediate;

            while (getline(check1, intermediate, ','))
            {
                tokens.push_back(intermediate);
            }

            auto job = new domain::Job(domain::jobTypeFromString(tokens[1]),
                                       stoi(tokens[2]),
                                       domain::powerLevelFromString(tokens[3]));

            auto preset = domain::Preset(tokens[0], *job);

            entities.push_back(preset);
        }
        presetsFile.close();
    }
}