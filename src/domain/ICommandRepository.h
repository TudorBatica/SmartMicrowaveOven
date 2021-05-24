#pragma once
#include <vector>
#include "../domain/Command.h"

namespace domain
{
    class ICommandRepository
    {
    public:
        virtual std::vector<domain::Command> findAll() = 0;
        virtual void add(domain::Command) = 0;
    };
}