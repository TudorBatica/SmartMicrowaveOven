#include "PresetService.h"

namespace service
{
    PresetService::PresetService(domain::IPresetRepository *repository)
    {
        this->repository = repository;
    }

    std::vector<domain::Preset> PresetService::getPresets()
    {
        return repository->findAll();
    }

    domain::Preset PresetService::getPresetById(int presetId)
    {
        return repository->findById(presetId);
    }

    domain::Preset *PresetService::getPresetByFood(std::string food)
    {
        return repository->findByFood(food);
    }

    void PresetService::addPreset(domain::Preset preset)
    {
        repository->add(preset);
    }
}