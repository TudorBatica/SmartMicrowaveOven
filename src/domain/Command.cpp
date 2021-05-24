#include "Command.h"

namespace domain
{
    int Command::nextId = 0;

    Command::Command() {}

    Command::Command(std::string time, Preset preset)
    {
        this->commandId = nextId;
        this->time = time;
        this->preset = preset;
        nextId++;
    }

    void Command::setPreset(Preset preset)
    {
        this->preset = preset;
    }

    Preset Command::getPreset()
    {
        return preset;
    }

    void Command::setTime(std::string time)
    {
        this->time = time;
    }

    std::string Command::getTime()
    {
        return time;
    }

    int Command::getCommandId()
    {
        return commandId;
    }

    std::string Command::toString()
    {
        return std::to_string(commandId) + " " + time + " " + preset.toString();
    }

    std::string Command::toJson()
    {
        return "{\n\t\"commandId\": " + std::to_string(commandId)
                + ",\n\t\"time\": \"" + time 
                + "\",\n\t\"preset\": \t" + preset.toJson() + "\n}";
    }
}
