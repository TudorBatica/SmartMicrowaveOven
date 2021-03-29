#pragma once

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include "../../Microwave.h"
#include "../infrastructure/IPresetRepository.h"

class MicrowaveEndpoint
{
public:
    explicit MicrowaveEndpoint(Pistache::Address addr, Infrastructure::IPresetRepository *presetRepository);
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

    Infrastructure::IPresetRepository *presetRepository;

    void setupRoutes();

    void getPresets(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void addPreset(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);

    void doAuth(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void setSetting(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
    void getSetting(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response);
};