#include "PresetRepository.h"
#include <algorithm>

namespace Infrastructure
{
    domain::Preset PresetRepository::findByFood(std::string food)
    {
        return *std::find_if(entities.begin(), entities.end(), [food](domain::Preset &p) { return !p.getFood().compare(food); });
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