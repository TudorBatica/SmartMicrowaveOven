#include "IPresetRepository.h"

namespace Infrastructure
{
    class PresetRepository : public IPresetRepository
    {
    public:
        std::vector<domain::Preset> findAll();
        domain::Preset findByFood(std::string food);
        void add(domain::Preset preset);
    private:
        std::vector<domain::Preset> entities;
    };
}