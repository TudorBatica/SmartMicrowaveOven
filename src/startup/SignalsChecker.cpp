#include "SignalsChecker.h"

bool SignalsChecker::areAllSignalsOk(sigset_t signals)
{
    if (sigemptyset(&signals) != 0 || sigaddset(&signals, SIGTERM) != 0 
    || sigaddset(&signals, SIGINT) != 0 || sigaddset(&signals, SIGHUP) != 0 
    || pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0) 
    {
        return false;
    }

    return true;
}