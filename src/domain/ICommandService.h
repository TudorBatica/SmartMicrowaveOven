#pragma once
#include "../domain/Command.h"
#include <vector>

namespace domain
{
    class ICommandService
    {
    public:
        virtual std::vector<domain::Command> getCommands() = 0;
        virtual void addCommand(domain::Command command) = 0;
    };
}