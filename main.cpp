#include "ArgumentsParser.h"
#include "Microwave.h"
#include "SignalsChecker.h"
#include "src/presentation/MicrowaveEndpoint.h"
#include "src/infrastructure/PresetRepository.h"

using namespace Pistache;

int main(int argc, char *argv[])
{    
    sigset_t signals;
    if (!SignalsChecker::areAllSignalsOk(signals))
    {
        perror("Install Signal Handler Failed");
        return 1;
    }
    
    std::pair<Pistache::Port, int> portAndThreads = ArgumentsParser::getNoOfThreadsAndPortFromArgv(argc, argv);

    Address addr(Ipv4::any(), portAndThreads.first);

    std::cout << "Cores = " << hardware_concurrency() << '\n';
    std::cout << "Using " << portAndThreads.second << " threads" << '\n';

    // Instance of the class that defines what the server can do.
    auto *presetRepo = new Infrastructure::PresetRepository();
    MicrowaveEndpoint server(addr, presetRepo);

    // Initialize and start the server
    server.init(portAndThreads.second);
    server.startThreaded();

    // Code that waits for the shutdown sinal for the server
    
    int signal = 0;
    int status = sigwait(&signals, &signal);
    if (status == 0)
    {
        std::cout << "received signal " << signal << std::endl;
    }
    else
    {
        std::cerr << "sigwait returns " << status << std::endl;
    }

    server.stop();
}