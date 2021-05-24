#include "PresetRepository.h"
#include <algorithm>

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
    }
}