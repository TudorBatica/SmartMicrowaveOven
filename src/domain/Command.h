#pragma once

#include <string>
#include "Preset.h"

namespace domain
{
    class Command
    {
    public:
        Command();
        Command(std::string time, Preset preset);

        void setPreset(Preset preset);
        Preset getPreset();

        void setTime(std::string time);
        std::string getTime();

        int getCommandId();

        std::string toString();
        std::string toJson();

    private:
        static int nextId;
        int commandId;
        std::string time;
        Preset preset;
    };

}
