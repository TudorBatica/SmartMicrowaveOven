#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "../domain/IPresetService.h"

class MicrowaveEndpoint
{
public:
    explicit MicrowaveEndpoint(Pistache::Address addr, domain::IPresetService *presetService);
    void init(size_t thr = 2);
    void startThreaded();
    void stop();

private:
    domain::IPresetService *presetService;
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    Pistache::Rest::Router router;

    void setupRoutes();

    void getPresets(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void addPreset(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
};