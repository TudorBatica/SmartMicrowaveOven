#pragma once
#include <vector>
#include "../domain/Preset.h"

namespace domain
{
    class IPresetRepository
    {
    public:
        virtual std::vector<domain::Preset> findAll() = 0;
        virtual domain::Preset findByFood(std::string food) = 0;
        virtual domain::Preset findById(int presetId) = 0;
        virtual void add(domain::Preset) = 0;
    };
} 