#pragma once
#include "../domain/ICommandService.h"
#include "../domain/ICommandRepository.h"

namespace service
{
    class CommandService : public domain::ICommandService
    {
    public:
        CommandService(domain::ICommandRepository *repository);

        std::vector<domain::Command> getCommands();
        void addCommand(domain::Command Command);

    private:
        domain::ICommandRepository *repository;
    };
}
