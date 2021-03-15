#pragma once

#include <string>

class Microwave
{
public:
    explicit Microwave() {}
    int set(std::string name, std::string value);
    std::string get(std::string name);

private:
    struct boolSetting
    {
        std::string name;
        bool value;
    } defrost;
};