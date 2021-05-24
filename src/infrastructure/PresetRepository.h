#include "../domain/IPresetRepository.h"

namespace infrastructure
{
    class PresetRepository : public domain::IPresetRepository
    {
    public:
        std::vector<domain::Preset> findAll();
        domain::Preset findById(int presetId);
        domain::Preset *findByFood(std::string food);
        void add(domain::Preset preset);
    private:
        std::vector<domain::Preset> entities;
    };
}