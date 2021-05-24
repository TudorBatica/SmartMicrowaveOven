#include "startup/ArgumentsParser.h"
#include "startup/SignalsChecker.h"
#include "presentation/MicrowaveEndpoint.h"
#include "infrastructure/PresetRepository.h"
#include "service/PresetService.h"
#include "infrastructure/CommandRepository.h"
#include "service/CommandService.h"
#include <string>

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

    auto *presetRepo = new infrastructure::PresetRepository();
    auto *presetService = new service::PresetService(presetRepo);
    auto *commandRepo = new infrastructure::CommandRepository();
    auto *commandService = new service::CommandService(commandRepo);
    MicrowaveEndpoint server(addr, presetService, commandService);

    server.init(portAndThreads.second);
    server.startThreaded();
    int signal = 0;
    int status = sigwait(&signals, &signal);
    server.stop();
}