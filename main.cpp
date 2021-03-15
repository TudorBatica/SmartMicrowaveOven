#include "ArgumentsParser.h"
#include "Microwave.h"
#include "MicrowaveEndpoint.h"
#include "SignalsChecker.h"

using namespace std;
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

    cout << "Cores = " << hardware_concurrency() << endl;
    cout << "Using " << portAndThreads.second << " threads" << endl;

    // Instance of the class that defines what the server can do.
    MicrowaveEndpoint stats(addr);

    // Initialize and start the server
    stats.init(portAndThreads.second);
    stats.startThreaded();

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

    stats.stop();
}