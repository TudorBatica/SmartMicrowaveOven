#include "CommandRepository.h"
#include <algorithm>

namespace infrastructure
{
    std::vector<domain::Command> CommandRepository::findAll()
    {
        return entities;
    }

    void CommandRepository::add(domain::Command command)
    {
        entities.push_back(command);
    }
}