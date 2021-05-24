#pragma once
#include "../domain/IPresetService.h"
#include "../domain/IPresetRepository.h"

namespace service
{
    class PresetService : public domain::IPresetService
    {
    public:
        PresetService(domain::IPresetRepository *repository);

        std::vector<domain::Preset> getPresets();
        domain::Preset getPresetById(int presetId);
        domain::Preset *getPresetByFood(std::string food);
        void addPreset(domain::Preset preset);

    private:
        domain::IPresetRepository *repository;
    };
}
