#pragma once
#include "../domain/Preset.h"
#include <vector>

namespace domain
{
    class IPresetService
    {
    public:
        virtual std::vector<domain::Preset> getPresets() = 0;
        virtual void addPreset(domain::Preset preset) = 0;
    };
}