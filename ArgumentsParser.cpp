#include "ArgumentsParser.h"
#include <string>

std::pair<Pistache::Port, int> ArgumentsParser::getNoOfThreadsAndPortFromArgv(int argc, char* argv[])
{
    Pistache::Port port = (argc > 1) ? Pistache::Port(std::stol(argv[1])) : Pistache::Port(DEFAULT_PORT);
    int threads = (argc > 2) ? std::stoi(argv[2]) : DEFAULT_NUMBER_OF_THREADS;

    return std::make_pair(port, threads);
}