#include "CommandService.h"

namespace service
{
    CommandService::CommandService(domain::ICommandRepository *repository)
    {
        this->repository = repository;
    }

    std::vector<domain::Command> CommandService::getCommands()
    {
        return repository->findAll();
    }

    void CommandService::addCommand(domain::Command Command)
    {
        repository->add(Command);
    }
}