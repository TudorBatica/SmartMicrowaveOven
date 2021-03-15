#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>

#include "Microwave.h"

class MicrowaveEndpoint
{
public:
    explicit MicrowaveEndpoint(Pistache::Address addr);
    void init(size_t thr = 2);
    void startThreaded();
    void stop();

private:
    using Lock = std::mutex;
    using Guard = std::lock_guard<Lock>;
    Lock microwaveLock;
    Microwave mwv;
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;
    
    void setupRoutes();
    void doAuth(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void setSetting(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void getSetting(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
};