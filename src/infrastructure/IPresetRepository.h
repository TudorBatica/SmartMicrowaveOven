#pragma once
#include <vector>
#include "../domain/Preset.h"

namespace infrastructure
{
    class IPresetRepository
    {
    public:
        virtual std::vector<domain::Preset> findAll() = 0;
        virtual domain::Preset findByFood(std::string food) = 0;
        virtual void add(domain::Preset) = 0;
    };
} // namespace Infrastructure