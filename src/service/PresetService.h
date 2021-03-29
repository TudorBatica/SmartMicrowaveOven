#pragma once
#include "IPresetService.h"
#include "../infrastructure/IPresetRepository.h"

namespace service
{
    class PresetService : public IPresetService
    {
    public:
        PresetService(Infrastructure::IPresetRepository *repository);

        std::vector<domain::Preset> getPresets();
        void addPreset(domain::Preset preset);

    private:
        Infrastructure::IPresetRepository *repository;
    };
}
