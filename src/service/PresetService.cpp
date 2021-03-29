#include "PresetService.h"

namespace service
{
    PresetService::PresetService(Infrastructure::IPresetRepository *repository)
    {
        this->repository = repository;
    }

    std::vector<domain::Preset> PresetService::getPresets()
    {
        return repository->findAll();
    }

    void PresetService::addPreset(domain::Preset preset)
    {
        repository->add(preset);
    }
}