#include <signal.h>

class SignalsChecker
{
    public:
        static bool areAllSignalsOk(sigset_t signals);
    private:
        SignalsChecker(){}
};