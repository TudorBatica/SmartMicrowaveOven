#include "ArgumentsParser.h"
#include "Microwave.h"
#include "SignalsChecker.h"
#include "src/presentation/MicrowaveEndpoint.h"
#include "src/infrastructure/PresetRepository.h"
#include "src/service/PresetService.h"

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

    auto *presetRepo = new Infrastructure::PresetRepository();
    auto *presetService = new service::PresetService(presetRepo);
    MicrowaveEndpoint server(addr, presetService);


    server.init(portAndThreads.second);
    server.startThreaded();

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