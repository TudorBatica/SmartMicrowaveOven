#include "../domain/ICommandRepository.h"

namespace infrastructure
{
    class CommandRepository : public domain::ICommandRepository
    {
    public:
        std::vector<domain::Command> findAll();
        void add(domain::Command command);
    private:
        std::vector<domain::Command> entities;
    };
}