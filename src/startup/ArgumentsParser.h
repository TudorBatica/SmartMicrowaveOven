#pragma once

#include <utility>
#include <pistache/endpoint.h>

class ArgumentsParser
{
    public:
        static std::pair<Pistache::Port, int> getNoOfThreadsAndPortFromArgv(int argc, char* argv[]);
    private:
        ArgumentsParser() {}
        static const int DEFAULT_NUMBER_OF_THREADS = 2;
        static const int DEFAULT_PORT = 9080;
};